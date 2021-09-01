#version 150
// ^ Change this to version 130 if you have compatibility issues

// describes the weights of the joints that influence the given vertex
in vec2 vs_weights;
// contains the IDs of the joints that influence the given vertex
in ivec2 vs_jointIDs;

uniform mat4 u_Model;
uniform mat4 u_ViewProj;

// uniform array of matrices that each describe the bind matrix of a particular joint
uniform mat4 unif_bindMats[100];
// uniform array of matrices that each describe the current overall transformation of a particular joint
uniform mat4 unif_currOverallTransforms[100];

in vec4 vs_Pos;
in vec4 vs_Col;

out vec4 fs_Col;

void main()
{
    fs_Col = vs_Col;        // Pass the vertex colors to the fragment shader for interpolation

    vec4 pos_1 = unif_currOverallTransforms[vs_jointIDs[0]] *
                 unif_bindMats[vs_jointIDs[0]] * vs_Pos;
    vec4 pos_2 = unif_currOverallTransforms[vs_jointIDs[1]] *
                 unif_bindMats[vs_jointIDs[1]] * vs_Pos;

    vec4 pos = vs_weights[0] * pos_1 + vs_weights[1] * pos_2;
    vec4 modelposition = u_Model * pos;

    gl_Position = u_ViewProj * modelposition;
}

