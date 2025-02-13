/******************************Module*Header*******************************\
* Module Name: nstate.h
*
* NORMAL_STATE
*
* Copyright 1995 - 1998 Microsoft Corporation
*
\**************************************************************************/

#ifndef __nstate_h__
#define __nstate_h__

#include "sscommon.h"
#include "objects.h"
#include "state.h"

#define NORMAL_PIPE_COUNT       5
#define NORMAL_TEX_PIPE_COUNT   3

#define NUM_JOINT_STYLES        3


// styles for pipe joints
enum {
    ELBOWS = 0,
    BALLS,
    EITHER
};

// joint types
enum {
    ELBOW_JOINT = 0,
    BALL_JOINT
};

// shchemes for choosing directions
enum {
    NORMAL_SCHEME_CHOOSE_DIR_RANDOM,
    NORMAL_SCHEME_CHOOSE_DIR_TURN,
    NORMAL_SCHEME_CHOOSE_DIR_STRAIGHT
};

// this used for traditional pipe drawing

class PIPE_OBJECT;
class ELBOW_OBJECT;
class SPHERE_OBJECT;
class BALLJOINT_OBJECT;

class STATE;


class NORMAL_STATE {
public:
    int             jointStyle;
    int             bCycleJointStyles;
    
    PIPE_OBJECT     *shortPipe;
    PIPE_OBJECT     *longPipe;
    ELBOW_OBJECT    *elbows[4];
    SPHERE_OBJECT   *ballCap;
    SPHERE_OBJECT   *bigBall;
    BALLJOINT_OBJECT  *ballJoints[4];

    NORMAL_STATE( STATE *pState );
    ~NORMAL_STATE();
    void            Reset();
//    int             GetMaxPipesPerFrame();
    void            BuildObjects( float radius, float divSize, int nSlices,
                                  BOOL bTexture, IPOINT2D *pTexRep );  
    int             ChooseJointType();
};

#endif // __nstate_h__
