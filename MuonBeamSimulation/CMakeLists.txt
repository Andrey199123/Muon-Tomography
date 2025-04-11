cmake_minimum_required(VERSION 3.10)
project(MuonBeamSimulation)

# Find Geant4 package
find_package(Geant4 REQUIRED)
link_directories(${Geant4_LIBRARY_DIRS})
# Include directories
include_directories(${Geant4_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cc
    src/DetectorConstruction.cc
    src/PrimaryGeneratorAction.cc
    src/PhysicsList.cc
    src/RunAction.cc
    src/EventAction.cc
    src/ActionInitialization.cc
    src/SteppingAction.cc
)

add_executable(MuonBeamSimulation ${SOURCES})
target_link_libraries(MuonBeamSimulation ${Geant4_LIBRARIES})
