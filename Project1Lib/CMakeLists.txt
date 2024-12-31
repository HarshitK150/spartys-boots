project(Project1Lib)

set(SOURCE_FILES
    MainFrame.cpp
    MainFrame.h
    pch.h
    GameView.cpp
    GameView.h
    Game.cpp
    Game.h
    Item.cpp
    Item.h
    IDraggable.h
    Gate.cpp
    Gate.h
    Items/Product.cpp
    Items/Product.h
    Items/Conveyor.cpp
    Items/Conveyor.h
    Items/Scoreboard.cpp
    Items/Scoreboard.h
    Gates/Sparty.cpp
    Gates/Sparty.h
    Gates/Beam.cpp
    Gates/Beam.h
    Items/Badge.cpp
    Items/Badge.h
    InputPin.cpp
    InputPin.h
    OutputPin.cpp
    OutputPin.h
    Gates/SensorGate.cpp
    Gates/SensorGate.h
    Items/Sensor.cpp
    Items/Sensor.h
    Gates/ORGate.cpp
    Gates/ORGate.h
    Items/LevelNotice.cpp
    Items/LevelNotice.h
    IDraggable.h
    ids.h
    Gates/NOTGate.cpp
    Gates/NOTGate.h
    Gates/ANDGate.cpp
    Gates/ANDGate.h
    States.h
    Visitors/ItemVisitor.h
    Score.cpp
    Score.h
    Gates/DFlipFlop.cpp
    Gates/DFlipFlop.h
    Gates/SRFlipFlop.cpp
    Gates/SRFlipFlop.h
    XmlLoader.cpp
    XmlLoader.h
    Visitors/KickVisitor.cpp
    Visitors/KickVisitor.h
    Visitors/ProductAnimator.h
    Visitors/ScoreVisitor.cpp
    Visitors/ScoreVisitor.h
    Visitors/BadgeVisitor.cpp
    Visitors/BadgeVisitor.h
    Visitors/SensorVisitor.cpp
    Visitors/SensorVisitor.h
        Visitors/ZeroScoreVisitor.h
        Visitors/ZeroScoreVisitor.cpp
        Visitors/LevelScoreUpdateVisitor.cpp
        Visitors/LevelScoreUpdateVisitor.h
    Visitors/BeamProductVisitor.cpp
    Visitors/BeamProductVisitor.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})