# API Documentation - Qt HMI Display UI

## RadialBar Component (C++)

### Overview
The `RadialBar` class is a custom Qt Quick component that provides a highly configurable radial progress bar suitable for dashboard applications.

### Class Definition
```cpp
class RadialBar : public QQuickPaintedItem
```

### Properties

#### Core Properties
| Property | Type | Description | Default |
|----------|------|-------------|---------|
| `size` | qreal | Overall size of the radial bar | - |
| `startAngle` | qreal | Starting angle in degrees | 270 |
| `spanAngle` | qreal | Span angle for the arc | 360 |
| `minValue` | qreal | Minimum value | 0 |
| `maxValue` | qreal | Maximum value | 100 |
| `value` | qreal | Current value | 0 |
| `dialWidth` | int | Width of the dial stroke | 17 |

#### Visual Properties
| Property | Type | Description |
|----------|------|-------------|
| `backgroundColor` | QColor | Background color of the dial |
| `foregroundColor` | QColor | Foreground/dial color |
| `progressColor` | QColor | Color of the progress arc |
| `textColor` | QColor | Color of the display text |
| `penStyle` | Qt::PenCapStyle | Style of the pen (Round, Square, Flat) |

#### Text Properties
| Property | Type | Description |
|----------|------|-------------|
| `suffixText` | QString | Text to append to the value |
| `showText` | bool | Whether to display text |
| `textFont` | QFont | Font for the display text |

#### Dial Types
```cpp
enum DialType {
    FullDial,    // Complete circle
    MinToMax,    // Arc from min to max
    NoDial       // No background dial
};
```

### Usage Example
```qml
import CustomControls 1.0

RadialBar {
    id: batteryGauge
    width: 300
    height: 300
    
    minValue: 0
    maxValue: 100
    value: 65
    
    startAngle: 270
    spanAngle: 360
    dialWidth: 15
    
    backgroundColor: "transparent"
    progressColor: "#01E4E0"
    textColor: "#FFFFFF"
    
    penStyle: Qt.RoundCap
    dialType: RadialBar.NoDial
    
    showText: true
    suffixText: "%"
    
    textFont {
        family: "Inter"
        pixelSize: 32
        bold: Font.Medium
    }
}
```

## Gauge Component (QML)

### Overview
A custom circular gauge component with advanced styling and color-coded zones.

### Properties
| Property | Type | Description |
|----------|------|-------------|
| `speedColor` | string | Current speed zone color |
| `value` | real | Current gauge value |
| `minimumValue` | real | Minimum gauge value |
| `maximumValue` | real | Maximum gauge value |

### Methods
#### speedColorProvider(value)
Returns color based on speed zones:
- Green: 0-60
- Yellow: 60-150  
- Red: 150+

### Usage Example
```qml
Gauge {
    id: speedometer
    width: 450
    height: 450
    
    minimumValue: 0
    maximumValue: 300
    value: 120
    
    // Interactive properties
    property bool accelerating: false
    
    Behavior on value { 
        NumberAnimation { duration: 1000 }
    }
    
    // Keyboard handling
    Keys.onSpacePressed: accelerating = true
    Keys.onReleased: {
        if (event.key === Qt.Key_Space) {
            accelerating = false
        }
    }
}
```

## Main Application Functions

### Global Functions (main.qml)

#### generateRandom(maxLimit)
```qml
function generateRandom(maxLimit = 70) {
    let rand = Math.random() * maxLimit;
    rand = Math.floor(rand);
    return rand;
}
```
Generates random integer up to maxLimit.

#### speedColor(value)
```qml
function speedColor(value) {
    if(value < 60) {
        return "green"
    } else if(value > 60 && value < 150) {
        return "yellow"
    } else {
        return "Red"
    }
}
```
Returns color string based on speed value.

### Timer Components

#### Clock Timer
```qml
Timer {
    interval: 500
    running: true
    repeat: true
    onTriggered: {
        currentTime.text = Qt.formatDateTime(new Date(), "hh:mm")
    }
}
```
Updates the dashboard clock every 500ms.

#### Speed Update Timer
```qml
Timer {
    repeat: true
    interval: 3000
    running: true
    onTriggered: {
        nextSpeed = generateRandom()
    }
}
```
Updates speed limit display every 3 seconds.

## Styling Guidelines

### Color Palette
```qml
// Primary Colors
background: "#1E1E1E"
accent: "#01E6DE"
success: "#32D74B"
warning: "yellow"
danger: "Red"
text: "#FFFFFF"

// Opacity Variants
textSecondary: "#FFFFFF" (opacity: 0.8)
textTertiary: "#FFFFFF" (opacity: 0.2)
```

### Typography
```qml
// Font Stack
fontFamily: "Inter"

// Font Weights
normal: Font.Normal
medium: Font.Medium  
demiBold: Font.DemiBold
bold: Font.Bold

// Font Sizes
small: 20
medium: 28-32
large: 45-60
xlarge: 85-134
```

### Animation
```qml
// Standard Duration
Behavior on value { 
    NumberAnimation { duration: 1000 }
}

// Quick Transitions
Behavior on indicator { 
    NumberAnimation { duration: 300 }
}
```

## Resource Management

### QRC Structure
```xml
<RCC>
    <qresource prefix="/">
        <file>main.qml</file>
        <file>Gauge.qml</file>
        <file alias="assets/Dashboard.svg">assets/Dashboard.svg</file>
        <!-- ... other assets -->
    </qresource>
</RCC>
```

### Asset Loading
```qml
// Correct asset referencing
source: "qrc:/assets/filename.svg"

// Asynchronous loading for better performance
Image {
    source: "qrc:/assets/image.png"
    asynchronous: true
    sourceSize.width: width
}
```

## Performance Optimization

### Best Practices
1. **Use `asynchronous: true` for images**
2. **Limit timer intervals appropriately**
3. **Use `Behavior` animations for smooth transitions**
4. **Optimize paint() method in custom components**
5. **Cache expensive calculations**

### Memory Management
- Use object pooling for dynamic elements
- Properly manage QML object lifecycle
- Avoid memory leaks in C++ components