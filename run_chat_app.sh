#!/bin/bash

# Define variables
BUILD_DIR="build"
EXECUTABLE="ChatServer"
PYTHON_PORT=8000

# Function to start the Python HTTP server
start_http_server() {
    echo "Starting Python HTTP server..."
    python3 -m http.server "$PYTHON_PORT" &
    HTTP_SERVER_PID=$!
    echo "HTTP server running on port $PYTHON_PORT with PID $HTTP_SERVER_PID"
}

# Function to run the WebSocket server
start_websocket_server() {
    echo "Starting WebSocket server..."
    "$BUILD_DIR/$EXECUTABLE" &
    WEBSOCKET_SERVER_PID=$!
    echo "WebSocket server running with PID $WEBSOCKET_SERVER_PID"
}

# Function to stop all background processes
cleanup() {
    echo "Stopping servers..."
    if [ -n "$HTTP_SERVER_PID" ]; then
        kill "$HTTP_SERVER_PID"
    fi
    if [ -n "$WEBSOCKET_SERVER_PID" ]; then
        kill "$WEBSOCKET_SERVER_PID"
    fi
    exit
}

# Trap INT and TERM signals to cleanup
trap cleanup INT TERM

# Main script
# Check if the executable exists
if [ ! -f "$BUILD_DIR/$EXECUTABLE" ]; then
    echo "Error: Executable $EXECUTABLE not found. Please build the project first."
    exit 1
fi

start_websocket_server
start_http_server

# Keep the script running to keep servers up
wait

