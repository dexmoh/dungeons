#include "camera_controller.hpp"

#include "game.hpp"

CameraController::CameraController()
    : _ctx{ nullptr }, _camera{ 0.0f }, _position { Vector2i::ZERO }
{}

void CameraController::init(Game* ctx) {
    _ctx = ctx;

    recenter();
    set_position(_position);

    _camera.rotation = 0.0f;
    _camera.zoom = DEFAULT_ZOOM;
}

void CameraController::update(float delta) {
    // Check if window resized;
    if (IsWindowResized())
        recenter();

    // Handle movement.
    if (IsKeyPressed(KEY_UP)) {
        set_position(_position + Vector2i::UP);
    }
    else if (IsKeyPressed(KEY_DOWN)) {
        set_position(_position + Vector2i::DOWN);
    }
    else if (IsKeyPressed(KEY_LEFT)) {
        set_position(_position + Vector2i::LEFT);
    }
    else if (IsKeyPressed(KEY_RIGHT)) {
        set_position(_position + Vector2i::RIGHT);
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
    }
}

void CameraController::recenter() {
    _camera.offset = (Vector2) {
        GetScreenWidth() / 2.0f,
        GetScreenHeight() / 2.0f
    };
}

Camera2D CameraController::get_rl_camera() const { return _camera; }
float CameraController::get_rotation() const { return _camera.rotation; }

void CameraController::set_position(Vector2i position) {
    _position = position;
    Vector2i tile_size = _ctx->get_tile_size();

    _camera.target = (Vector2) {
        _position.x * tile_size.width() + (tile_size.width() / 2.0f),
        -_position.y * tile_size.height() - (tile_size.height() / 2.0f)
    };
}

void CameraController::set_rotation(float new_rotation) { _camera.rotation = new_rotation; }
