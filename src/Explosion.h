//
//  Explosion.h
//
//  Created by Nathaniel Pawelczyk on 4/10/13.
//  Copyright (c) 2013 Nathaniel Pawelczyk. All rights reserved.
//

#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "GraphicsHeader.h"
#include <vector>
#include "Particle.h"

class Explosion
{
private:
    float* camx;  //pointers to camera position; used pointers so camera location always current
    float* camy;
    float* camz;
    
    
public:
    std::vector<Particle> particles;
    double* yawAngle;
    Explosion(float x, float y, float z, float vx, float vy, float vz, float* cx, float* cy, float* cz)  //initialize explosion
    {
        camx = cx;
        camy = cy;
        camz = cz;
        
        for(int i = 0; i < 300; i++)
        {
            int splash = 0;
            if(y<2) splash = 1;
            Particle p(x, y, z, vx, vy, vz,splash);
            particles.push_back(p);
        }
    }
    
    bool drawExplosion()  //returns true if explosion has disappeared after this iteration
    {
        for(int i = 0; i < particles.size(); i++)
        {
            if(particles[i].advanceState())
            {
                //particles[i].advanceState();
                float x = particles[i].x;
                float y = particles[i].y;
                float z = particles[i].z;
                
                glColor4f(particles[i].r,particles[i].g, particles[i].b, particles[i].life+.3);
                
                //billboardSphericalBegin(*camx, *camy, *camz, x, y, z);
                
                glTranslatef(x, y, z);
                glPushMatrix();
                glRotatef(90-*yawAngle, 0, 1, 0);
                glBegin(GL_TRIANGLE_STRIP);
                //glVertex3f(x+0.3f, y+0.3f, z);
                //glVertex3f(x-0.3f, y+0.3f, z);
                //glVertex3f(x+0.3f, y-0.3f, z);
                //glVertex3f(x-0.3f, y-0.3f, z);
                glVertex3f(0.3f, 0.3f, 0);
                glVertex3f(-0.3f, 0.3f, 0);
                glVertex3f(0.3f, -0.3f, 0);
                glVertex3f(-0.3f, -0.3f, 0);
                glEnd();
                glPopMatrix();
                glTranslatef(-x, -y, -z);
     
                
                glPopMatrix();
            }
            else
            {
                particles.erase(particles.begin() + i);  //erase particle if it is transparent
            }
        }
        
        return (particles.size() == 0);
    }
    

};

#endif
