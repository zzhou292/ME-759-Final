%{

/* Includes the header in the wrapper code */
#include "chrono/core/ChCoordsys.h"

%}
 
 %import "ChQuaternion.i"

/* Parse the header file to generate wrappers */
%include "../../chrono/core/ChCoordsys.h" 


%template(ChCoordsysD) chrono::ChCoordsys<double>; 
//%template(ChCoordsysF) chrono::ChCoordsys<float>; 
