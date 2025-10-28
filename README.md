# Qt HMI Display UI - Car Dashboard

A modern car dashboard interface built with Qt Quick and QML, featuring real-time gauges, interactive controls, and a sleek electric vehicle-inspired design.

![Car Dashboard](assets/Dashboard.svg)

## 🚗 Features

### Core Dashboard Elements
- **Digital Speedometer**: Interactive circular gauge with color-coded speed indicators
- **Battery Charge Display**: Radial progress bar showing battery percentage
- **Speed Limit Indicator**: Dynamic speed limit display with color-coded warnings
- **Real-time Clock**: Live time and date display
- **Vehicle Status**: Gear selector and ready status indicators

### Interactive Controls
- **Headlight Toggle**: Clickable headlight indicator
- **Keyboard Controls**: 
  - `Space`: Accelerate
  - `Enter/Return`: Brake/Decelerate
  - `Ctrl+Q`: Quit application

### Visual Indicators
- **Speed Bar**: 7-segment horizontal speed indicator
- **Temperature Display**: Current temperature reading
- **Vehicle Statistics**: Distance, fuel usage, and average speed
- **Full-screen Mode**: Optimized for 1920x960 resolution

## 🛠️ Technical Architecture

### Components
- **main.cpp**: Application entry point and QML engine setup
- **main.qml**: Main dashboard interface
- **Gauge.qml**: Custom circular speedometer component
- **RadialBar**: Custom C++ component for radial progress bars
- **Assets**: SVG icons and background images

### Custom Components

#### RadialBar (C++)
A custom QQuickPaintedItem that provides:
- Configurable start/span angles
- Custom colors and styling
- Text display options
- Multiple dial types (Full, MinToMax, NoDial)

#### Gauge (QML)
A styled CircularGauge featuring:
- Color-coded speed zones (Green: 0-60, Yellow: 60-150, Red: 150+)
- Animated needle with glow effect
- Custom tickmarks and labels
- Gradient arc visualization

## 📋 Requirements

### System Requirements
- Qt 5.15 or later
- Qt Quick Controls 2.5+
- Qt Quick Extras 1.4+
- QtGraphicalEffects 1.0+

### Build Dependencies
- qmake
- C++11 compatible compiler
- Qt development libraries

## 🚀 Installation & Setup

### 1. Clone or Download
```bash
git clone [repository-url]
cd Dashboard
```

### 2. Build with qmake
```bash
qmake Car_1.pro
make
```

### 3. Run Application
```bash
./Car_1
```

## 🎮 Usage

### Keyboard Controls
| Key | Action |
|-----|--------|
| `Space` | Accelerate vehicle |
| `Enter`/`Return` | Brake/Decelerate |
| `Ctrl+Q` | Exit application |

### Interactive Elements
- **Headlight Icon**: Click to toggle headlight status
- **Speedometer**: Responds to keyboard input for acceleration
- **Battery Gauge**: Shows charging status with animation

## 🏗️ Project Structure

```
Dashboard/
├── main.cpp                 # Application entry point
├── main.qml                 # Main dashboard interface
├── Gauge.qml                # Custom speedometer component
├── radialbar.h/.cpp         # Custom radial progress bar
├── Car_1.pro                # Qt project file
├── qml.qrc                  # QML resource file
├── Makefile                 # Build configuration
├── assets/                  # Graphics and icons
│   ├── Dashboard.svg        # Main dashboard background
│   ├── Car.svg             # Vehicle illustration
│   ├── needle.svg          # Speedometer needle
│   ├── background.svg      # Gauge background
│   └── ...                 # Various UI icons
└── README.md               # This documentation
```

## 🎨 Customization

### Colors
The dashboard uses a dark theme with accent colors:
- **Primary Background**: `#1E1E1E`
- **Accent Color**: `#01E6DE` (Cyan)
- **Success Color**: `#32D74B` (Green)
- **Warning Color**: `yellow`
- **Danger Color**: `Red`

### Fonts
- **Primary Font**: Inter
- **Weight**: Normal, DemiBold, Bold
- **Sizes**: 20px - 134px

### Modifying Components

#### Speed Limits
Edit the `speedColor()` function in `main.qml`:
```qml
function speedColor(value){
    if(value < 60 ){
        return "green"
    } else if(value > 60 && value < 150){
        return "yellow"
    } else {
        return "Red"
    }
}
```

#### Battery Display
Modify the RadialBar properties in `main.qml`:
```qml
RadialBar {
    maxValue: 100
    progressColor: "#01E4E0"
    dialWidth: 17
    // ... other properties
}
```

## 🔧 Development

### Adding New Gauges
1. Create a new QML component similar to `Gauge.qml`
2. Register any C++ components in `main.cpp`
3. Add to the main interface in `main.qml`

### Custom C++ Components
Follow the RadialBar pattern:
1. Inherit from `QQuickPaintedItem`
2. Define Q_PROPERTY macros for QML binding
3. Implement paint() method for custom drawing
4. Register with `qmlRegisterType`

### Asset Management
- Add new SVG/PNG files to the `assets/` directory
- Update `qml.qrc` to include new resources
- Reference with `qrc:/assets/filename.ext`

## 🐛 Troubleshooting

### Common Issues

1. **Build Errors**
   - Ensure Qt development packages are installed
   - Check Qt version compatibility (5.15+)

2. **Missing Assets**
   - Verify all files are included in `qml.qrc`
   - Check file paths use forward slashes

3. **Performance Issues**
   - Enable hardware acceleration
   - Reduce timer intervals if needed

### Debug Mode
Run with debug output:
```bash
QML_CONSOLE_LOG_LEVEL=debug ./Car_1
```
