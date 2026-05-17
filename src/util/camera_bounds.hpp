#pragma once

// Container struct for holding camera's world-space bounding box.
struct CameraBounds {
    int start_x; // Left-most coordinate.
    int start_y; // Bottom-most coordinate.
    int end_x;   // Right-most coordinate.
    int end_y;   // Top-most coordinate.
};
