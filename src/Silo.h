//
//  Silo.h
//  FinalProjectFund2
//
//  Created by Matt McGlynn on 4/19/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef FinalProjectFund2_Silo_h
#define FinalProjectFund2_Silo_h



#include <iostream>
#include <vector>
#include "Bullet.h"
#include <math.h>
#include "GraphicsHeader.h"


class Silo : public ComputerPlane{
    
    
    
    
public:
    double siloRadius;
    Silo():ComputerPlane(){
        manuverability = 4;
    }
    
    
    void drawSilo(){
        
        glTranslatef(x, y, z);
       
        
        
        
        
        glColor3f(.16, .16, .16);
        
        glPushMatrix();
        glRotatef(planeYaw, 1, 0, 0);
        glRotatef(roll, 0, 0, 1);
        glRotatef(pitch, 0, 1, 0);
        glutSolidSphere(siloRadius, 15, 15);
        glutSolidCone(siloRadius*.25, -siloRadius*3, 20, 20);
        glPopMatrix();
        
        double height = siloRadius*1.1;
        //Draw Command Tower
        double baseX = 0;
        double baseY = 0;
        double baseZ = 0;
        double cubeHeight = height;
        double cubeWidth = height;
        double maxX = baseX + cubeWidth;
        double maxY = baseY + cubeWidth;
        double maxZ = baseZ + cubeHeight;
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
        //glFrontFace(GL_CW);
        /*
        glBegin(GL_QUADS);
        
        //X face
        glVertex3d(baseX, baseZ, baseY);
        glVertex3d(baseX, baseZ, maxY);
        glVertex3d(baseX, maxZ, maxY);
        glVertex3d(baseX, maxZ, baseY );
        
        
        //Y face
        glVertex3d(baseX, baseZ, baseY );
        glVertex3d(maxX, baseZ, baseY );
        glVertex3d(maxX, maxZ, baseY );
        glVertex3d(baseX, maxZ, baseY );
        
        //maxX face
        glVertex3d(maxX, baseZ, baseY );
        glVertex3d(maxX, baseZ, maxY);
        glVertex3d(maxX, maxZ, maxY);
        glVertex3d(maxX, maxZ, baseY );
        
        //maxY face
        glVertex3d(baseX, baseZ, maxY);
        glVertex3d(maxX, baseZ, maxY);
        glVertex3d(maxX, maxZ, maxY);
        glVertex3d(baseX, maxZ, maxY);
        
        //Building Top
        glVertex3d(baseX, maxZ, baseY);
        glVertex3d(maxX, maxZ, baseY);
        glVertex3d(maxX, maxZ, maxY);
        glVertex3d(baseX, maxZ, maxY);

        
        glEnd();
         */
        glTranslatef(-x, -y, -z);
        
        
        
        
    }};

#endif

