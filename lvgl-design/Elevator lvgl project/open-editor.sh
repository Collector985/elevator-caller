#!/bin/bash
# Quick script to open LVGL project in VSCode with editor

PROJECT_DIR="/home/collector985/lstore/Documents/PlatformIO/Projects/elevator-caller/lvgl-design/Elevator lvgl project"

echo "🚀 Opening LVGL project in VSCode..."
cd "$PROJECT_DIR"
code .

echo ""
echo "✅ VSCode should now be open with the project"
echo ""
echo "📝 Next steps:"
echo "   1. Press Ctrl+Shift+P"
echo "   2. Type: LVGL: Open Editor"
echo "   3. Start designing!"
echo ""
