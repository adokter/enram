/*
 * Copyright 2013 Netherlands eScience Center
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



/******************************************************************************/
/*Definition of standard parameters.                                          */
/******************************************************************************/

#define DEG2RAD    (0.017453293)  /*Degrees to radians.*/

/******************************************************************************/
/*Definition of general macros:                                               */
/******************************************************************************/

#define XABS(x)    (((x)<0)?(-(x)):(x))
#define SIGN(x)    (((x)<0)?-1:1)
#define ROUND(x)   (((x)>0)?(int)((x)+0.5):(int)((x)-0.5))
#define SQUARE(x)  ((x)*(x))
#define XYMAX(x,y) (((x)<(y))?(y):(x))
#define XYMIN(x,y) (((x)<(y))?(x):(y))

/******************************************************************************/
/*Defined (default) parameters.                                               */
/******************************************************************************/

#define TEXCV       (1)
#define TEXSTDEV    (2)
#define NEIGHBOURS  (5)      /*Minimum number of directly neighouring pixels  */
                             /*with dBZ>DBZRAIN [1-8]                         */
#define NDATA       (3)      /*Data dimension height layers.                  */

/******************************************************************************/
/*Definition of parameters for sorting:                                       */
/******************************************************************************/
#define BYAREA      (1)
#define BYMEAN      (2)


///******************************************************************************/
///*Structure for containing SCAN metadata:                                     */
///******************************************************************************/

struct scanmeta {
    float heig;              // Height of radar antenna in km.
    float elev;              // Elevation of scan in deg.
    int nRang;               // Number of range bins in scan.
    int nAzim;               // Number of azimuth rays in scan.
    float rangeScale;        // Size of range bins in scan in km.
    float azimScale;         // Size of azimuth steps in scan in deg.
    float valueOffset;       // Offset value of quantity contained by scan.
    float valueScale;        // Scale of value of quantity contained by scan.
    int missing;             // Missing value of quantity contained by scan.
};

struct cellprop {
    int iRangOfMax;
    int iAzimOfMax;
    float dbzAvg;
    float texAvg;
    float cv;
    float area;
    float clutterArea;
    float dbzMax;
    int index;
    char drop;
};

typedef struct scanmeta SCANMETA;
typedef struct cellprop CELLPROP;




// *****************************************************************************
// Function prototypes
// *****************************************************************************

int analysecells(unsigned char *dbzImage,unsigned char *vradImage,
                 unsigned char *texImage, unsigned char *clutterImage, int *cellImage,
                 SCANMETA *dbzMeta, SCANMETA *vradMeta, SCANMETA *texMeta, SCANMETA *clutterMeta,
                 int nCells, int areaMin, float cellDbzMin, float cellStdDevMax, float cellClutterFraction,
                 float vradMinValue,float dbzClutterMin, unsigned char cmFlag,
                 unsigned char dualPolFlag, unsigned char verbose);

void classification(SCANMETA dbzMeta, SCANMETA vradMeta, SCANMETA uzmeta,
        SCANMETA clutterMeta, int *cellImage,
        unsigned char *dbzImage, unsigned char *vradImage,
        unsigned char *uzscan, unsigned char *clutterImage,
        float *zdata,
        float rangeMin, float rangeMax, float HLAYER, float XOFFSET,
        float XSCALE, float XMEAN, float height,
        float azimMin, float azimMax, float vradMin, float dbzClutter, float dbzMin,
        float dBZx, float DBZNOISE, int NGAPMIN, int NGAPBIN, int NDBZMIN,
        int layer, int *np, int *nPointsPtr, int *nPointsAllPtr, int *nPointsClutterPtr,
        int *nPointsRainPtr, int *nPointsRainNoFringePtr,
        unsigned char clutterFlag, unsigned char uzflag, unsigned char xflag);

float dist(int range1, int azim1,int range2,int azim2,float rscale,float ascale);

int findcells(unsigned char *texImage,
              unsigned char *rhoImage,
              unsigned char *zdrImage,
              int *cellImage,
              SCANMETA *texMeta,
              SCANMETA *rhoMeta,
              SCANMETA *zdrMeta,
              float texThresMin,
              float rhoThresMin,
              float zdrThresMin,
              float reflThresMin,
              float rCellMax,
              char sign);

void fringecells(int *cellImage,int nRang, int nAzim, float aScale, float rScale, float fringe);

void sortcells(CELLPROP *cellProp,int nCells, int method);

void texture(unsigned char *texImage,unsigned char *vradImage, unsigned char *reflImage,
        SCANMETA *texMeta,SCANMETA *vradMeta,SCANMETA *reflMeta,
        unsigned char nRangNeighborhood,unsigned char nAzimNeighborhood,
        unsigned char nCountMin,unsigned char texType);

int updatemap(int *cellImage,CELLPROP *cellProp, int nCells,int nGlobal, int minCellArea);

void vvp(SCANMETA vradMeta, unsigned char *vradImage, float *points, float *yObs,
        int *c, int *cellmap, int nDims, int *nPointsMaxPtr, int NGAPBIN,
        float rangeMin, float rangeMax, float HLAYER, float heightInputPar,
        float vradMin, int iData, int layer, int id, int *nPoints);




