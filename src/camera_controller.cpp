#include "camera_controller.hpp"

#include "game.hpp"
#include "atoms/atom.hpp"
#include "level.hpp"

CameraController::CameraController(Game& ctx)
    : _ctx{ ctx },
      _target{ nullptr },
      _camera{ 0.0f },
      _position { Vector2i::ZERO },
      _offset { 0.0f, 0.0f },
      _bounds{ 0 }
{}

CameraController::~CameraController() {
    _ctx.window_resized.disconnect(_win_resized_id);
}

void CameraController::init() {
    _win_resized_id = _ctx.window_resized.connect(
        [this](int width, int height) {
            _recenter(width, height);
        }
    );

    _recenter(
        GetScreenWidth(),
        GetScreenHeight()
    );

    set_position(_position, false);

    _camera.rotation = 0.0f;
    _camera.zoom = DEFAULT_ZOOM;

    _recalculate_bounds();
}

void CameraController::update(float delta) {
    if (_target) {
        set_offset(_target->get_offset(), false);

        if (_target->get_position() != _position)
            set_position(_target->get_position());
    }

    // Handle zoom.
    if (IsKeyPressed(KEY_Z)) {
        // Zoom out.
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            _camera.zoom /= ZOOM_FACTOR;
            if (_camera.zoom < MIN_ZOOM)
                _camera.zoom = MIN_ZOOM;
        }
        // Zoom in.
        else {
            _camera.zoom *= ZOOM_FACTOR;
            if (_camera.zoom > MAX_ZOOM)
                _camera.zoom = MAX_ZOOM;
        }

        _recalculate_bounds();
    }
}

void CameraController::_recenter(int width, int height) {
    _camera.offset = (Vector2) {
        width / 2.0f,
        height / 2.0f
    };

    _recalculate_bounds();
}

void CameraController::_recalculate_bounds() {
    Vector2i tile_size = _ctx.get_tile_size();

    Vector2 world_btm_left = GetScreenToWorld2D(
        { 0, float(GetScreenHeight()) }, _camera
    );
    world_btm_left.y = -world_btm_left.y;

    Vector2 world_top_right = GetScreenToWorld2D(
        { float(GetScreenWidth()), 0 }, _camera
    );
    world_top_right.y = -world_top_right.y;

    _bounds = {
        int(world_btm_left.x / tile_size.width()),
        int(world_btm_left.y / tile_size.height()),
        int(world_top_right.x / tile_size.width()),
        int(world_top_right.y / tile_size.height())
    };

    // Add a 1 tile buffer around the bounding box.
    _bounds.start_x -= 1;
    _bounds.start_y -= 1;
    _bounds.end_x += 2;
    _bounds.end_y += 2;

    // Clamp bounding box.
    _bounds.start_x = (_bounds.start_x < 0) ? 0 : _bounds.start_x;
    _bounds.start_y = (_bounds.start_y < 0) ? 0 : _bounds.start_y;

    if (_ctx.get_level()) {
        Vector2i lvl_size = _ctx.get_level()->get_size();

        _bounds.end_x = (_bounds.end_x > lvl_size.width()) ? lvl_size.width() : _bounds.end_x;
        _bounds.end_y = (_bounds.end_y > lvl_size.height()) ? lvl_size.height() : _bounds.end_y;
    }
}

/* Getters & Setters */
Atom* CameraController::get_target() { return _target; }
Camera2D CameraController::get_rl_camera() const { return _camera; }
CameraBounds CameraController::get_bounds() const { return _bounds; }

void CameraController::set_target(Atom* target) {
    if (_target && _target_deleted_id != SIGNAL_NULL_ID) {
        _target->deleted.disconnect(_target_deleted_id);
        _target_deleted_id = SIGNAL_NULL_ID;
    }

    if (target)
        _target_deleted_id = target->deleted.connect(
            [this]() {
                _target = nullptr;
                _target_deleted_id = SIGNAL_NULL_ID;
            }
        );

    _target = target;
}

void CameraController::set_position(Vector2i position, bool recalculate_bounds) {
    _position = position;
    Vector2i tile_size = _ctx.get_tile_size();

    _camera.target = {
        _position.x * tile_size.width() + (tile_size.width() / 2.0f) + _offset.x,
        -_position.y * tile_size.height() - (tile_size.height() / 2.0f) - _offset.y
    };

    if (recalculate_bounds)
        _recalculate_bounds();
}

void CameraController::set_offset(Vector2 offset, bool recalculate_bounds) {
    _offset = offset;
    set_position(_position, recalculate_bounds);
}
