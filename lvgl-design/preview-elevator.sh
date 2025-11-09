#!/bin/bash
# Free Preview Script for Elevator LVGL Design
# No payment required!

PROJECT_DIR="/home/collector985/lstore/Documents/PlatformIO/Projects/elevator-caller"
SIMULATOR_DIR="$PROJECT_DIR/crowpanel-display/lv_port_linux"

echo "=========================================="
echo "  🚀 Free Elevator UI Preview"
echo "=========================================="
echo ""

# Check if SDL is installed
if ! dpkg -l | grep -q libsdl2-dev; then
    echo "📦 Installing SDL2 (required for preview)..."
    sudo apt-get update
    sudo apt-get install -y libsdl2-dev cmake build-essential
fi

# Build the simulator
echo "🔨 Building simulator..."
cd "$SIMULATOR_DIR"

# Use existing build or create new one
if [ ! -d "build" ]; then
    mkdir build
fi

cd build

# Configure with SDL backend
cmake .. -DLV_USE_SDL=1
make -j$(nproc)

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Build successful!"
    echo ""
    echo "🎨 Launching preview window (480×800)..."
    echo ""
    ./lvglsim -b SDL -W 480 -H 800
else
    echo "❌ Build failed. Check errors above."
    exit 1
fi
