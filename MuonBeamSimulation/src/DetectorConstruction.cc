#include "DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"

DetectorConstruction::DetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();

    G4double worldSize = 20.0 * m;

    G4Material* worldMaterial = nist->FindOrBuildMaterial("G4_AIR");


    G4Box* worldSolid = new G4Box("World", worldSize / 2, worldSize / 2, worldSize / 2);
    G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid, worldMaterial, "World");
    G4VPhysicalVolume* worldPhysical = new G4PVPlacement(
        nullptr, G4ThreeVector(), worldLogical, "World", nullptr, false, 0);

    G4double outerRadius = 1.25 * m;         
    G4double outerThickness = 0.3 * m;       
    G4double containerHeight = 3.2 * m;      

    G4Tubs* outerShellSolid = new G4Tubs(
        "OuterShell",                        
        0,                                   
        outerRadius,                         
        containerHeight / 2,                 
        0.0 * deg,                           
        360.0 * deg                          
    );

    G4Material* steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    G4LogicalVolume* outerShellLogical = new G4LogicalVolume(
        outerShellSolid, steel, "OuterShellLogical");

    G4VisAttributes* outerVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.5)); 
    outerVisAtt->SetVisibility(true);
    outerShellLogical->SetVisAttributes(outerVisAtt);

    new G4PVPlacement(
        nullptr,                              
        G4ThreeVector(0, 0, 0),               
        outerShellLogical,                    
        "OuterShell",                         
        worldLogical,                         
        false,                                
        0                                     
    );

    G4double airGapThickness = 0.1 * m;       
    G4double airGapRadius = outerRadius - outerThickness;

    G4Tubs* airGapSolid = new G4Tubs(
        "AirGap",                             
        0,                                    
        airGapRadius,                         
        containerHeight / 2,                  
        0.0 * deg,                            
        360.0 * deg                           
    );

    G4LogicalVolume* airGapLogical = new G4LogicalVolume(
        airGapSolid, worldMaterial, "AirGapLogical");

    G4VisAttributes* airGapVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.2)); 
    airGapVisAtt->SetVisibility(true);
    airGapLogical->SetVisAttributes(airGapVisAtt);

    new G4PVPlacement(
        nullptr,                              
        G4ThreeVector(0, 0, 0),               
        airGapLogical,                       
        "AirGap",                            
        outerShellLogical,                    
        false,                               
        0                                     
    );


    G4double innerLinerThickness = 0.05 * m;  
    G4double innerLinerRadius = airGapRadius - airGapThickness;

    G4Tubs* innerLinerSolid = new G4Tubs(
        "InnerLiner",                         
        0,                                    
        innerLinerRadius,                     
        containerHeight / 2,                  
        0.0 * deg,                            
        360.0 * deg                         
    );

    G4LogicalVolume* innerLinerLogical = new G4LogicalVolume(
        innerLinerSolid, steel, "InnerLinerLogical");


    G4VisAttributes* innerLinerVisAtt = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0, 0.5)); 
    innerLinerVisAtt->SetVisibility(true);
    innerLinerLogical->SetVisAttributes(innerLinerVisAtt);

    new G4PVPlacement(
        nullptr,                              
        G4ThreeVector(0, 0, 0),               
        innerLinerLogical,                   
        "InnerLiner",                         
        airGapLogical,                        
        false,                                
        0                                     
    );

    G4double wasteRadius = innerLinerRadius - innerLinerThickness;

    G4Tubs* wasteSolid = new G4Tubs(
        "WasteMatrix",                        
        0,                                    
        wasteRadius,                          
        containerHeight / 2,                  
        0.0 * deg,                            
        360.0 * deg                           
    );

    G4Material* wasteMaterial = nist->FindOrBuildMaterial("G4_CONCRETE"); 
    G4LogicalVolume* wasteLogical = new G4LogicalVolume(
        wasteSolid, wasteMaterial, "WasteLogical");

    G4VisAttributes* wasteVisAtt = new G4VisAttributes(G4Colour(0.8, 0.4, 0.0, 0.5)); 
    wasteVisAtt->SetVisibility(true);
    wasteLogical->SetVisAttributes(wasteVisAtt);

    new G4PVPlacement(
        nullptr,                              
        G4ThreeVector(0, 0, 0),               
        wasteLogical,                         
        "WasteMatrix",                        
        innerLinerLogical,                    
        false,                               
        0                                     
    );

    return worldPhysical;
}
