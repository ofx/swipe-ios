//
//  GamestateManager.h
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/16/11.
//  Copyright 2011 ofx. All rights reserved.
//

#pragma once

#include "ResourceManager.h"
#include "RenderingEngine.hpp"
#include "Disc.hpp"

#include <string>

class GamestateManager 
{
private:
    bool m_Pause;
    
    int m_Multiplier, m_Score, m_ScorePerTimeframe;
    time_t m_LastScore;
    
    Disc **m_Discs;
public:
    GamestateManager ( void );
    ~GamestateManager ( void );
    
    void Initialize ( ResourceManager *resourcemanager );
    
    void Reset( void );
    
    void Update( void );
    void Score( Vector2 scoreposition );
    
    void CheckField( void );
    
    int GetMultiplier( void ) { return m_Multiplier; }
    int GetScore( void ) { return m_Score; }
    Disc **GetDiscs( void ) { return m_Discs; }
};