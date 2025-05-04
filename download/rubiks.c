#include <stdio.h>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#define SDL_MAIN_HANDLED
#include "stb_image.h"
#include <SDL2/SDL.h>
#define CGLM_USE_DOUBLE
#include <cglm/cglm.h>
#include <cglm/affine.h>
#include <stdbool.h>



int main(){
    SDL_Window *window = NULL;
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        printf("error in window initialization\n");
        return 1;
    }
    window = SDL_CreateWindow("rubiks",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000,1000,SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GLContext *context = SDL_GL_CreateContext(window);
    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
        printf("error in glad initialization\n");
        return 1;
    }

    glViewport(0, 0, 1000, 1000);
glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    


    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location=0) in vec3 aPos;\n"
    "layout (location=1) in vec2 Coords;\n"
    "out vec2 texCoords;\n"
    "uniform mat4 view;\n"
    "uniform mat4 model;\n"
    "uniform mat4 perspective;\n"
    "uniform mat4 trans;\n"
    "void main()\n"
    "{\n"
    "gl_Position = perspective*view*model*trans*vec4(aPos,1.0f);\n"
    "texCoords = Coords;\n"
    "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
    "in vec2 texCoords;\n"
    "out vec4 fragColor;\n"
    "uniform sampler2D pic;\n"
    "void main()\n"
    "{\n"
    "fragColor = texture(pic,texCoords);\n"
    "}\0";

    unsigned int vertexShader,fragmentShader,shaderprogram;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);
    unsigned int success;
    char infolog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infolog);
        printf("Error in vertex shader compilation %s \n",infolog);
        return 1;
    }
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragmentShader,512,NULL,infolog);
        printf("Error in fragment shader compilation %s \n",infolog);
        return 1;
    }
    shaderprogram = glCreateProgram();
    glAttachShader(shaderprogram,vertexShader);
    glAttachShader(shaderprogram,fragmentShader);
    glLinkProgram(shaderprogram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(shaderprogram, 512, NULL, infoLog);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
}

    unsigned int tex1,tex2,tex3,tex4,tex5,tex6;
    int width,height,channels;
    

    unsigned char *data = stbi_load("real.png",&width,&height,&channels,STBI_rgb_alpha);
    if(data){
        glGenTextures(1,&tex1);
        glBindTexture(GL_TEXTURE_2D,tex1);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("error in initializing image %s \n",stbi_failure_reason());
        return 1;
    }

    data = stbi_load("realyellow.png",&width,&height,&channels,STBI_rgb_alpha);
    
    if(data){
        glGenTextures(1,&tex2);
        glBindTexture(GL_TEXTURE_2D,tex2);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("error in initializing image %s \n",stbi_failure_reason());
        return 1;
    }

    data = stbi_load("realorange.png",&width,&height,&channels,STBI_rgb_alpha);
    
    if(data){
        glGenTextures(1,&tex3);
        glBindTexture(GL_TEXTURE_2D,tex3);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("error in initializing image %s \n",stbi_failure_reason());
        return 1;
    }

    data = stbi_load("realred.png",&width,&height,&channels,STBI_rgb_alpha);
    
    if(data){
        glGenTextures(1,&tex4);
        glBindTexture(GL_TEXTURE_2D,tex4);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("error in initializing image %s \n",stbi_failure_reason());
        return 1;
    }

    data = stbi_load("newwhite.png",&width,&height,&channels,STBI_rgb_alpha);
    
    if(data){
        glGenTextures(1,&tex5);
        glBindTexture(GL_TEXTURE_2D,tex5);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("error in initializing image %s \n",stbi_failure_reason());
        return 1;
    }

    data = stbi_load("realgreen.png",&width,&height,&channels,STBI_rgb_alpha);
    
    if(data){
        glGenTextures(1,&tex6);
        glBindTexture(GL_TEXTURE_2D,tex6);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("error in initializing image %s \n",stbi_failure_reason());
        return 1;
    }


    glUseProgram(shaderprogram);
    
    
    unsigned int vbo,vao;
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void *)3);
    glEnableVertexAttribArray(1);
    
    struct cube{
        vec4 position;
        vec4 original;
        mat4 trans;
        mat4 model;
    };
    
    struct cube byo;
    glm_mat4_identity(byo.model);
    glm_mat4_identity(byo.trans);
    byo.position[0] = 0.0f;
    byo.position[1] = 0.0f;
    byo.position[2] = 0.0f;
    byo.position[3] = 1.0f;
    glm_translate(byo.trans,(vec3){1.0f,1.0f,1.0f});
    glm_mat4_mulv(byo.trans,byo.position,byo.position);
    glm_vec4_copy(byo.position,byo.original);
    

    struct cube by;
    glm_mat4_identity(by.model);
    glm_mat4_identity(by.trans);
    by.position[0] = 0.0f;
    by.position[1] = 0.0f;
    by.position[2] = 0.0f;
    by.position[3] = 1.0f;
    glm_translate(by.trans,(vec3){1.0f,1.0f,0.0f});
    glm_mat4_mulv(by.trans,by.position,by.position);
    glm_vec4_copy(by.position,by.original);
    

    struct cube byr;
    glm_mat4_identity(byr.model);
    glm_mat4_identity(byr.trans);
    byr.position[0] = 0.0f;
    byr.position[1] = 0.0f;
    byr.position[2] = 0.0f;
    byr.position[3] = 1.0f;
    glm_translate(byr.trans,(vec3){1.0f,1.0f,-1.0f});
    glm_mat4_mulv(byr.trans,byr.position,byr.position);
    glm_vec4_copy(byr.position,byr.original);
    

    struct cube bo;
    glm_mat4_identity(bo.model);
    glm_mat4_identity(bo.trans);
    bo.position[0] = 0.0f;
    bo.position[1] = 0.0f;
    bo.position[2] = 0.0f;
    bo.position[3] = 1.0f;
    glm_translate(bo.trans,(vec3){1.0f,0.0f,1.0f});
    glm_mat4_mulv(bo.trans,bo.position,bo.position);
    glm_vec4_copy(bo.position,bo.original);
    

    struct cube b;
    glm_mat4_identity(b.model);
    glm_mat4_identity(b.trans);
    b.position[0] = 0.0f;
    b.position[1] = 0.0f;
    b.position[2] = 0.0f;
    b.position[3] = 1.0f;
    glm_translate(b.trans,(vec3){1.0f,0.0f,0.0f});
    glm_mat4_mulv(b.trans,b.position,b.position);
    glm_vec4_copy(b.position,b.original);
    

    struct cube br;
    glm_mat4_identity(br.model);
    glm_mat4_identity(br.trans);
    br.position[0] = 0.0f;
    br.position[1] = 0.0f;
    br.position[2] = 0.0f;
    br.position[3] = 1.0f;
    glm_translate(br.trans,(vec3){1.0f,0.0f,-1.0f});
    glm_mat4_mulv(br.trans,br.position,br.position);
    glm_vec4_copy(br.position,br.original);

    struct cube bow;
    glm_mat4_identity(bow.model);
    glm_mat4_identity(bow.trans);
    bow.position[0] = 0.0f;
    bow.position[1] = 0.0f;
    bow.position[2] = 0.0f;
    bow.position[3] = 1.0f;
    glm_translate(bow.trans,(vec3){1.0f,-1.0f,1.0f});
    glm_mat4_mulv(bow.trans,bow.position,bow.position);
    glm_vec4_copy(bow.position,bow.original);

    struct cube bw;
    glm_mat4_identity(bw.model);
    glm_mat4_identity(bw.trans);
    bw.position[0] = 0.0f;
    bw.position[1] = 0.0f;
    bw.position[2] = 0.0f;
    bw.position[3] = 1.0f;
    glm_translate(bw.trans,(vec3){1.0f,-1.0f,0.0f});
    glm_mat4_mulv(bw.trans,bw.position,bw.position);
    glm_vec4_copy(bw.position,bw.original);

    struct cube brw;
    glm_mat4_identity(brw.model);
    glm_mat4_identity(brw.trans);
    brw.position[0] = 0.0f;
    brw.position[1] = 0.0f;
    brw.position[2] = 0.0f;
    brw.position[3] = 1.0f;
    glm_translate(brw.trans,(vec3){1.0f,-1.0f,-1.0f});
    glm_mat4_mulv(brw.trans,brw.position,brw.position);
    glm_vec4_copy(brw.position,brw.original);

    struct cube yo;
    glm_mat4_identity(yo.model);
    glm_mat4_identity(yo.trans);
    yo.position[0] = 0.0f;
    yo.position[1] = 0.0f;
    yo.position[2] = 0.0f;
    yo.position[3] = 1.0f;
    glm_translate(yo.trans,(vec3){0.0f,1.0f,1.0f});
    glm_mat4_mulv(yo.trans,yo.position,yo.position);
    glm_vec4_copy(yo.position,yo.original);

    struct cube y;
    glm_mat4_identity(y.model);
    glm_mat4_identity(y.trans);
    y.position[0] = 0.0f;
    y.position[1] = 0.0f;
    y.position[2] = 0.0f;
    y.position[3] = 1.0f;
    glm_translate(y.trans,(vec3){0.0f,1.0f,0.0f});
    glm_mat4_mulv(y.trans,y.position,y.position);
    glm_vec4_copy(y.position,y.original);

    struct cube yr;
    glm_mat4_identity(yr.model);
    glm_mat4_identity(yr.trans);
    yr.position[0] = 0.0f;
    yr.position[1] = 0.0f;
    yr.position[2] = 0.0f;
    yr.position[3] = 1.0f;
    glm_translate(yr.trans,(vec3){0.0f,1.0f,-1.0f});
    glm_mat4_mulv(yr.trans,yr.position,yr.position);
    glm_vec4_copy(yr.position,yr.original);

    struct cube o;
    glm_mat4_identity(o.model);
    glm_mat4_identity(o.trans);
    o.position[0] = 0.0f;
    o.position[1] = 0.0f;
    o.position[2] = 0.0f;
    o.position[3] = 1.0f;
    glm_translate(o.trans,(vec3){0.0f,0.0f,1.0f});
    glm_mat4_mulv(o.trans,o.position,o.position);
    glm_vec4_copy(o.position,o.original);

    struct cube r;
    glm_mat4_identity(r.model);
    glm_mat4_identity(r.trans);
    r.position[0] = 0.0f;
    r.position[1] = 0.0f;
    r.position[2] = 0.0f;
    r.position[3] = 1.0f;
    glm_translate(r.trans,(vec3){0.0f,0.0f,-1.0f});
    glm_mat4_mulv(r.trans,r.position,r.position);
    glm_vec4_copy(r.position,r.original);

    struct cube ow;
    glm_mat4_identity(ow.model);
    glm_mat4_identity(ow.trans);
    ow.position[0] = 0.0f;
    ow.position[1] = 0.0f;
    ow.position[2] = 0.0f;
    ow.position[3] = 1.0f;
    glm_translate(ow.trans,(vec3){0.0f,-1.0f,1.0f});
    glm_mat4_mulv(ow.trans,ow.position,ow.position);
    glm_vec4_copy(ow.position,ow.original);

    struct cube w;
    glm_mat4_identity(w.model);
    glm_mat4_identity(w.trans);
    w.position[0] = 0.0f;
    w.position[1] = 0.0f;
    w.position[2] = 0.0f;
    w.position[3] = 1.0f;
    glm_translate(w.trans,(vec3){0.0f,-1.0f,0.0f});
    glm_mat4_mulv(w.trans,w.position,w.position);
    glm_vec4_copy(w.position,w.original);

    struct cube rw;
    glm_mat4_identity(rw.model);
    glm_mat4_identity(rw.trans);
    rw.position[0] = 0.0f;
    rw.position[1] = 0.0f;
    rw.position[2] = 0.0f;
    rw.position[3] = 1.0f;
    glm_translate(rw.trans,(vec3){0.0f,-1.0f,-1.0f});
    glm_mat4_mulv(rw.trans,rw.position,rw.position);
    glm_vec4_copy(rw.position,rw.original);

    struct cube oyg;
    glm_mat4_identity(oyg.model);
    glm_mat4_identity(oyg.trans);
    oyg.position[0] = 0.0f;
    oyg.position[1] = 0.0f;
    oyg.position[2] = 0.0f;
    oyg.position[3] = 1.0f;
    glm_translate(oyg.trans,(vec3){-1.0f,1.0f,1.0f});
    glm_mat4_mulv(oyg.trans,oyg.position,oyg.position);
    glm_vec4_copy(oyg.position,oyg.original);

    struct cube yg;
    glm_mat4_identity(yg.model);
    glm_mat4_identity(yg.trans);
    yg.position[0] = 0.0f;
    yg.position[1] = 0.0f;
    yg.position[2] = 0.0f;
    yg.position[3] = 1.0f;
    glm_translate(yg.trans,(vec3){-1.0f,1.0f,0.0f});
    glm_mat4_mulv(yg.trans,yg.position,yg.position);
    glm_vec4_copy(yg.position,yg.original);

    struct cube ygr;
    glm_mat4_identity(ygr.model);
    glm_mat4_identity(ygr.trans);
    ygr.position[0] = 0.0f;
    ygr.position[1] = 0.0f;
    ygr.position[2] = 0.0f;
    ygr.position[3] = 1.0f;
    glm_translate(ygr.trans,(vec3){-1.0f,1.0f,-1.0f});
    glm_mat4_mulv(ygr.trans,ygr.position,ygr.position);
    glm_vec4_copy(ygr.position,ygr.original);

    struct cube og;
    glm_mat4_identity(og.model);
    glm_mat4_identity(og.trans);
    og.position[0] = 0.0f;
    og.position[1] = 0.0f;
    og.position[2] = 0.0f;
    og.position[3] = 1.0f;
    glm_translate(og.trans,(vec3){-1.0f,0.0f,1.0f});
    glm_mat4_mulv(og.trans,og.position,og.position);
    glm_vec4_copy(og.position,og.original);

    struct cube g;
    glm_mat4_identity(g.model);
    glm_mat4_identity(g.trans);
    g.position[0] = 0.0f;
    g.position[1] = 0.0f;
    g.position[2] = 0.0f;
    g.position[3] = 1.0f;
    glm_translate(g.trans,(vec3){-1.0f,0.0f,0.0f});
    glm_mat4_mulv(g.trans,g.position,g.position);
    glm_vec4_copy(g.position,g.original);

    struct cube gr;
    glm_mat4_identity(gr.model);
    glm_mat4_identity(gr.trans);
    gr.position[0] = 0.0f;
    gr.position[1] = 0.0f;
    gr.position[2] = 0.0f;
    gr.position[3] = 1.0f;
    glm_translate(gr.trans,(vec3){-1.0f,0.0f,-1.0f});
    glm_mat4_mulv(gr.trans,gr.position,gr.position);
    glm_vec4_copy(gr.position,gr.original);

    struct cube ogw;
    glm_mat4_identity(ogw.model);
    glm_mat4_identity(ogw.trans);
    ogw.position[0] = 0.0f;
    ogw.position[1] = 0.0f;
    ogw.position[2] = 0.0f;
    ogw.position[3] = 1.0f;
    glm_translate(ogw.trans,(vec3){-1.0f,-1.0f,1.0f});
    glm_mat4_mulv(ogw.trans,ogw.position,ogw.position);
    glm_vec4_copy(ogw.position,ogw.original);

    struct cube gw;
    glm_mat4_identity(gw.model);
    glm_mat4_identity(gw.trans);
    gw.position[0] = 0.0f;
    gw.position[1] = 0.0f;
    gw.position[2] = 0.0f;
    gw.position[3] = 1.0f;
    glm_translate(gw.trans,(vec3){-1.0f,-1.0f,0.0f});
    glm_mat4_mulv(gw.trans,gw.position,gw.position);
    glm_vec4_copy(gw.position,gw.original);

    struct cube gwr;
    glm_mat4_identity(gwr.model);
    glm_mat4_identity(gwr.trans);
    gwr.position[0] = 0.0f;
    gwr.position[1] = 0.0f;
    gwr.position[2] = 0.0f;
    gwr.position[3] = 1.0f;
    glm_translate(gwr.trans,(vec3){-1.0f,-1.0f,-1.0f});
    glm_mat4_mulv(gwr.trans,gwr.position,gwr.position);
    glm_vec4_copy(gwr.position,gwr.original);

    


    

    
    

    mat4 *arr[] = {
        &byo.model, &by.model, &byr.model,
        &bo.model, &b.model, &br.model,
        &bow.model, &bw.model, &brw.model,

        &yo.model, &y.model, &yr.model,
        &o.model, &r.model,
        &ow.model, &w.model, &rw.model,

        &oyg.model, &yg.model, &ygr.model,
        &og.model, &g.model, &gr.model,
        &ogw.model, &gw.model, &gwr.model
    };

    vec4 *posi[] = {
        &byo.position, &by.position, &byr.position,
        &bo.position, &b.position, &br.position,
        &bow.position, &bw.position, &brw.position,

        &yo.position, &y.position, &yr.position,
        &o.position, &r.position,
        &ow.position, &w.position, &rw.position,

        &oyg.position, &yg.position, &ygr.position,
        &og.position, &g.position, &gr.position,
        &ogw.position, &gw.position, &gwr.position
    };

    vec4 *origs[] = {
        &byo.original, &by.original, &byr.original,
        &bo.original, &b.original, &br.original,
        &bow.original, &bw.original, &brw.original,

        &yo.original, &y.original, &yr.original,
        &o.original, &r.original,
        &ow.original, &w.original, &rw.original,

        &oyg.original, &yg.original, &ygr.original,
        &og.original, &g.original, &gr.original,
        &ogw.original, &gw.original, &gwr.original
    };

    mat4 view,perspective;
    

    vec3 camerapos = {7.0f,7.0f,7.0f};
    glm_normalize(camerapos);
    vec3 right;
    glm_cross((vec3){0.0f,1.0f,0.0f},camerapos,right);
    glm_normalize(right);
    vec3 up;
    glm_cross(camerapos,right,up);
    
        glm_lookat((vec3){7.0f,7.0f,7.0f},(vec3){0.0f,0.0f,0.0f},up,view);
        
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"view"),1,GL_FALSE,(float *)view);
        glm_perspective(glm_rad(45.0f),1000.0f/1000.0f,0.1f,100.0f,perspective);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"perspective"),1,GL_FALSE,(float *)perspective);


        glClearColor(0.1f,0.2f,0.3f,1.0f);

        bool rotating=false;
        bool fullrotation = false;
        int steps;
    
    
    float angle;
    SDL_Event ev;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    bool running=true;
    int indices[9];
    int indexcounter=0;
    vec3 axis = {0.0f,0.0f,0.0f};
    SDL_GL_SwapWindow(window);
    while(running){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        while(SDL_PollEvent(&ev)){
            
        if(ev.type==SDL_QUIT){
            running=false;
            break;
        }
        else if(ev.type==SDL_KEYDOWN && rotating ==false && fullrotation==false){
            SDL_Keymod mod = SDL_GetModState();
            
            if(ev.key.keysym.sym==SDLK_r){
            rotating = true;
            steps=1;
            for(int i=0;i<26;i++){
                
                if(glm_vec4_eqv((vec4){1.0f,1.0f,1.0f,1.0f},*posi[i])){
                indices[indexcounter] = i;
                indexcounter++;
                
                }
                if(glm_vec4_eqv((vec4){1.0f,1.0f,0.0f,1.0f},*posi[i])){
                    indices[indexcounter] = i;
                    indexcounter++;
                    
                }
                if(glm_vec4_eqv((vec4){1.0f,1.0f,-1.0f,1.0f},*posi[i])){
                indices[indexcounter] = i;
                indexcounter++;
                
                }
                if(glm_vec4_eqv((vec4){1.0f,0.0f,1.0f,1.0f},*posi[i])){
                    indices[indexcounter] = i;
                    indexcounter++;
                    
                }
                if(glm_vec4_eqv((vec4){1.0f,0.0f,0.0f,1.0f},*posi[i])){
                    indices[indexcounter] = i;
                    indexcounter++;
                    
                }
                if(glm_vec4_eqv((vec4){1.0f,0.0f,-1.0f,1.0f},*posi[i])){
                    indices[indexcounter] = i;
                    indexcounter++;
                    
                }
                if(glm_vec4_eqv((vec4){1.0f,-1.0f,1.0f,1.0f},*posi[i])){
                    indices[indexcounter] = i;
                    indexcounter++;
                    
                }
                if(glm_vec4_eqv((vec4){1.0f,-1.0f,0.0f,1.0f},*posi[i])){
                    indices[indexcounter] = i;
                    indexcounter++;
                    
                }
                if(glm_vec4_eqv((vec4){1.0f,-1.0f,-1.0f,1.0f},*posi[i])){
                    indices[indexcounter] = i;
                    indexcounter++;
                    
                }
                
                
                
            }
            
            glm_vec3_copy((vec3){1.0f,0.0f,0.0f},axis);
            
            indexcounter=0;
            if((mod & KMOD_SHIFT))
            angle= 3.0f;
            else
            angle= (-3.0f);
            }


            


            if(ev.key.keysym.sym==SDLK_u){
                rotating = true;
                steps=1;
                for(int i=0;i<26;i++){
                    
                    if(glm_vec4_eqv((vec4){1.0f,1.0f,1.0f,1.0f},*posi[i])){
                    indices[indexcounter] = i;
                    
                    indexcounter++;
                    }
                    if(glm_vec4_eqv((vec4){1.0f,1.0f,0.0f,1.0f},*posi[i])){
                        indices[indexcounter] = i;
                        indexcounter++;
                    }
                    if(glm_vec4_eqv((vec4){1.0f,1.0f,-1.0f,1.0f},*posi[i])){
                    indices[indexcounter] = i;
                    indexcounter++;
                    }
                    if(glm_vec4_eqv((vec4){0.0f,1.0f,1.0f,1.0f},*posi[i])){
                        indices[indexcounter] = i;
                        indexcounter++;
                    }
                    if(glm_vec4_eqv((vec4){0.0f,1.0f,0.0f,1.0f},*posi[i])){
                        indices[indexcounter] = i;
                        indexcounter++;
                    }
                    if(glm_vec4_eqv((vec4){0.0f,1.0f,-1.0f,1.0f},*posi[i])){
                        indices[indexcounter] = i;
                        indexcounter++;
                    }
                    if(glm_vec4_eqv((vec4){-1.0f,1.0f,1.0f,1.0f},*posi[i])){
                        indices[indexcounter] = i;
                        indexcounter++;
                    }
                    if(glm_vec4_eqv((vec4){-1.0f,1.0f,0.0f,1.0f},*posi[i])){
                        indices[indexcounter] = i;
                        indexcounter++;
                    }
                    if(glm_vec4_eqv((vec4){-1.0f,1.0f,-1.0f,1.0f},*posi[i])){
                        indices[indexcounter] = i;
                        indexcounter++;
                    }
                    
                    
                    
                }
                glm_vec3_copy((vec3){0.0f,1.0f,0.0f},axis);
                
                indexcounter=0;
                if((mod & KMOD_SHIFT))
                angle= 3.0f;
                else
                angle= (-3.0f);
                }



            if(ev.key.keysym.sym==SDLK_l){
                    rotating = true;
                    steps=1;
                    for(int i=0;i<26;i++){
                        
                        if(glm_vec4_eqv((vec4){-1.0f,1.0f,1.0f,1.0f},*posi[i])){
                        indices[indexcounter] = i;
                        
                        indexcounter++;
                        }
                        if(glm_vec4_eqv((vec4){-1.0f,1.0f,0.0f,1.0f},*posi[i])){
                            indices[indexcounter] = i;
                            indexcounter++;
                        }
                        if(glm_vec4_eqv((vec4){-1.0f,1.0f,-1.0f,1.0f},*posi[i])){
                        indices[indexcounter] = i;
                        indexcounter++;
                        }
                        if(glm_vec4_eqv((vec4){-1.0f,0.0f,1.0f,1.0f},*posi[i])){
                            indices[indexcounter] = i;
                            indexcounter++;
                        }
                        if(glm_vec4_eqv((vec4){-1.0f,0.0f,0.0f,1.0f},*posi[i])){
                            indices[indexcounter] = i;
                            indexcounter++;
                        }
                        if(glm_vec4_eqv((vec4){-1.0f,0.0f,-1.0f,1.0f},*posi[i])){
                            indices[indexcounter] = i;
                            indexcounter++;
                        }
                        if(glm_vec4_eqv((vec4){-1.0f,-1.0f,1.0f,1.0f},*posi[i])){
                            indices[indexcounter] = i;
                            indexcounter++;
                        }
                        if(glm_vec4_eqv((vec4){-1.0f,-1.0f,0.0f,1.0f},*posi[i])){
                            indices[indexcounter] = i;
                            indexcounter++;
                        }
                        if(glm_vec4_eqv((vec4){-1.0f,-1.0f,-1.0f,1.0f},*posi[i])){
                            indices[indexcounter] = i;
                            indexcounter++;
                        }
                        
                        
                        
                    }
                    glm_vec3_copy((vec3){1.0f,0.0f,0.0f},axis);
                    
                    indexcounter=0;
                    if((mod & KMOD_SHIFT))
                    angle= -3.0f;
                    else
                    angle= (3.0f);
                    }

                if(ev.key.keysym.sym==SDLK_f){
                        rotating = true;
                        steps=1;
                        for(int i=0;i<26;i++){
                            
                            if(glm_vec4_eqv((vec4){1.0f,1.0f,1.0f,1.0f},*posi[i])){
                            indices[indexcounter] = i;
                            
                            indexcounter++;
                            }
                            if(glm_vec4_eqv((vec4){0.0f,1.0f,1.0f,1.0f},*posi[i])){
                                indices[indexcounter] = i;
                                indexcounter++;
                            }
                            if(glm_vec4_eqv((vec4){-1.0f,1.0f,1.0f,1.0f},*posi[i])){
                            indices[indexcounter] = i;
                            indexcounter++;
                            }
                            if(glm_vec4_eqv((vec4){1.0f,0.0f,1.0f,1.0f},*posi[i])){
                                indices[indexcounter] = i;
                                indexcounter++;
                            }
                            if(glm_vec4_eqv((vec4){0.0f,0.0f,1.0f,1.0f},*posi[i])){
                                indices[indexcounter] = i;
                                indexcounter++;
                            }
                            if(glm_vec4_eqv((vec4){-1.0f,0.0f,1.0f,1.0f},*posi[i])){
                                indices[indexcounter] = i;
                                indexcounter++;
                            }
                            if(glm_vec4_eqv((vec4){1.0f,-1.0f,1.0f,1.0f},*posi[i])){
                                indices[indexcounter] = i;
                                indexcounter++;
                            }
                            if(glm_vec4_eqv((vec4){0.0f,-1.0f,1.0f,1.0f},*posi[i])){
                                indices[indexcounter] = i;
                                indexcounter++;
                            }
                            if(glm_vec4_eqv((vec4){-1.0f,-1.0f,1.0f,1.0f},*posi[i])){
                                indices[indexcounter] = i;
                                indexcounter++;
                            }
                            
                            
                            
                        }
                        glm_vec3_copy((vec3){0.0f,0.0f,1.0f},axis);
                        
                        indexcounter=0;
                        if((mod & KMOD_SHIFT))
                        angle= 3.0f;
                        else
                        angle= (-3.0f);
                        }


                        if(ev.key.keysym.sym==SDLK_UP){
                            
                            fullrotation=true;
                            glm_vec3_copy((vec3){1.0f,0.0f,0.0f},axis);
                            angle= (-3.0f);
                        }

                        if(ev.key.keysym.sym==SDLK_DOWN){
                            
                            fullrotation=true;
                            glm_vec3_copy((vec3){1.0f,0.0f,0.0f},axis);
                            angle= (3.0f);
                        }

                        if(ev.key.keysym.sym==SDLK_RIGHT){
                            
                            fullrotation=true;
                            glm_vec3_copy((vec3){0.0f,1.0f,0.0f},axis);
                            angle= (3.0f);
                        }

                        if(ev.key.keysym.sym==SDLK_LEFT){
                            
                            fullrotation=true;
                            glm_vec3_copy((vec3){0.0f,1.0f,0.0f},axis);
                            angle= (-3.0f);
                        }
            
        }
    }

        if(rotating){
            
            mat4 temp;
            glm_rotate_make(temp,glm_rad(angle),axis);
            
            for(int i=0;i<9;i++)
            glm_mat4_mul(temp, *arr[indices[i]], *arr[indices[i]]);
            
            
            
            steps++;
            if(steps>30){
                for(int i=0;i<9;i++)
                glm_vec4_copy(*origs[indices[i]],*posi[indices[i]]);

                
                
                for(int i=0;i<9;i++)
                glm_mat4_mulv(*(arr[indices[i]]),*posi[indices[i]],*posi[indices[i]]);
                
                
            for(int i=0;i<4;i++){
                (*posi[indices[0]])[i] = roundf((*posi[indices[0]])[i]);
                (*posi[indices[1]])[i] = roundf((*posi[indices[1]])[i]);
                (*posi[indices[2]])[i] = roundf((*posi[indices[2]])[i]);
                (*posi[indices[3]])[i] = roundf((*posi[indices[3]])[i]);
                (*posi[indices[4]])[i] = roundf((*posi[indices[4]])[i]);
                (*posi[indices[5]])[i] = roundf((*posi[indices[5]])[i]);
                (*posi[indices[6]])[i] = roundf((*posi[indices[6]])[i]);
                (*posi[indices[7]])[i] = roundf((*posi[indices[7]])[i]);
                (*posi[indices[8]])[i] = roundf((*posi[indices[8]])[i]);
                
            }

            

            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    (*arr[indices[0]])[i][j] = roundf((*arr[indices[0]])[i][j]);
                    (*arr[indices[1]])[i][j] = roundf((*arr[indices[1]])[i][j]);
                    (*arr[indices[2]])[i][j] = roundf((*arr[indices[2]])[i][j]);
                    (*arr[indices[3]])[i][j] = roundf((*arr[indices[3]])[i][j]);
                    (*arr[indices[4]])[i][j] = roundf((*arr[indices[4]])[i][j]);
                    (*arr[indices[5]])[i][j] = roundf((*arr[indices[5]])[i][j]);
                    (*arr[indices[6]])[i][j] = roundf((*arr[indices[6]])[i][j]);
                    (*arr[indices[7]])[i][j] = roundf((*arr[indices[7]])[i][j]);
                    (*arr[indices[8]])[i][j] = roundf((*arr[indices[8]])[i][j]);
                    
                }
            }

            
                
                
            rotating=false;
            steps=1;
            }
        }


        if(fullrotation){
            
            mat4 temp;
            glm_rotate_make(temp,glm_rad(angle),axis);

            for(int i=0;i<26;i++)
            glm_mat4_mul(temp, *arr[i], *arr[i]);

            
            
            
            steps++;
            if(steps>30){
                
                for(int i=0;i<26;i++)
                glm_vec4_copy(*origs[i],*posi[i]);

                
                
                for(int i=0;i<26;i++)
                glm_mat4_mulv(*(arr[i]),*posi[i],*posi[i]);
                

                
            for(int j=0;j<26;j++){
            for(int i=0;i<4;i++){
                (*posi[j])[i] = roundf((*posi[j])[i]);
            }
        }

            
            for(int k=0;k<26;k++){
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    (*arr[k])[i][j] = roundf((*arr[k])[i][j]);
                    
                    
                }
            }
        }

            
            fullrotation=false;
            steps=1;
            }
        }

        
        
                
        
        
        glBindVertexArray(vao);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)byo.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)byo.trans);
        glBindTexture(GL_TEXTURE_2D,tex1);
        glDrawArrays(GL_TRIANGLES,18,6);
        glBindTexture(GL_TEXTURE_2D,tex2);
        glDrawArrays(GL_TRIANGLES,30,6);
        glBindTexture(GL_TEXTURE_2D,tex3);
        glDrawArrays(GL_TRIANGLES,6,6);

        
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)by.trans);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)by.model);
        
        
        glBindTexture(GL_TEXTURE_2D,tex1);
        glDrawArrays(GL_TRIANGLES,18,6);
        glBindTexture(GL_TEXTURE_2D,tex2);
        glDrawArrays(GL_TRIANGLES,30,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)byr.trans);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)byr.model);
        
        
        glBindTexture(GL_TEXTURE_2D,tex1);
        glDrawArrays(GL_TRIANGLES,18,6);
        glBindTexture(GL_TEXTURE_2D,tex2);
        glDrawArrays(GL_TRIANGLES,30,6);
        glBindTexture(GL_TEXTURE_2D,tex4);
        glDrawArrays(GL_TRIANGLES,0,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)bo.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)bo.trans);
        glBindTexture(GL_TEXTURE_2D,tex1);
        glDrawArrays(GL_TRIANGLES,18,6);
        glBindTexture(GL_TEXTURE_2D,tex3);
        glDrawArrays(GL_TRIANGLES,6,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)b.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)b.trans);
        glBindTexture(GL_TEXTURE_2D,tex1);
        glDrawArrays(GL_TRIANGLES,18,6);
        

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)br.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)br.trans);
        glBindTexture(GL_TEXTURE_2D,tex1);
        glDrawArrays(GL_TRIANGLES,18,6);
        glBindTexture(GL_TEXTURE_2D,tex4);
        glDrawArrays(GL_TRIANGLES,0,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)bow.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)bow.trans);
        glBindTexture(GL_TEXTURE_2D,tex3);
        glDrawArrays(GL_TRIANGLES,6,6);
        glBindTexture(GL_TEXTURE_2D,tex1);
        glDrawArrays(GL_TRIANGLES,18,6);
        glBindTexture(GL_TEXTURE_2D,tex5);
        glDrawArrays(GL_TRIANGLES,24,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)bw.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)bw.trans);
        glBindTexture(GL_TEXTURE_2D,tex1);
        glDrawArrays(GL_TRIANGLES,18,6);
        glBindTexture(GL_TEXTURE_2D,tex5);
        glDrawArrays(GL_TRIANGLES,24,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)brw.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)brw.trans);
        glBindTexture(GL_TEXTURE_2D,tex1);
        glDrawArrays(GL_TRIANGLES,18,6);
        glBindTexture(GL_TEXTURE_2D,tex5);
        glDrawArrays(GL_TRIANGLES,24,6);
        glBindTexture(GL_TEXTURE_2D,tex4);
        glDrawArrays(GL_TRIANGLES,0,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)yo.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)yo.trans);
        glBindTexture(GL_TEXTURE_2D,tex3);
        glDrawArrays(GL_TRIANGLES,6,6);
        glBindTexture(GL_TEXTURE_2D,tex2);
        glDrawArrays(GL_TRIANGLES,30,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)y.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)y.trans);
        glBindTexture(GL_TEXTURE_2D,tex2);
        glDrawArrays(GL_TRIANGLES,30,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)yr.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)yr.trans);
        glBindTexture(GL_TEXTURE_2D,tex4);
        glDrawArrays(GL_TRIANGLES,0,6);
        glBindTexture(GL_TEXTURE_2D,tex2);
        glDrawArrays(GL_TRIANGLES,30,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)o.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)o.trans);
        glBindTexture(GL_TEXTURE_2D,tex3);
        glDrawArrays(GL_TRIANGLES,6,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)r.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)r.trans);
        glBindTexture(GL_TEXTURE_2D,tex4);
        glDrawArrays(GL_TRIANGLES,0,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)ow.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)ow.trans);
        glBindTexture(GL_TEXTURE_2D,tex3);
        glDrawArrays(GL_TRIANGLES,6,6);
        glBindTexture(GL_TEXTURE_2D,tex5);
        glDrawArrays(GL_TRIANGLES,24,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)w.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)w.trans);
        glBindTexture(GL_TEXTURE_2D,tex5);
        glDrawArrays(GL_TRIANGLES,24,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)rw.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)rw.trans);
        glBindTexture(GL_TEXTURE_2D,tex4);
        glDrawArrays(GL_TRIANGLES,0,6);
        glBindTexture(GL_TEXTURE_2D,tex5);
        glDrawArrays(GL_TRIANGLES,24,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)oyg.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)oyg.trans);
        glBindTexture(GL_TEXTURE_2D,tex3);
        glDrawArrays(GL_TRIANGLES,6,6);
        glBindTexture(GL_TEXTURE_2D,tex6);
        glDrawArrays(GL_TRIANGLES,12,6);
        glBindTexture(GL_TEXTURE_2D,tex2);
        glDrawArrays(GL_TRIANGLES,30,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)yg.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)yg.trans);
        glBindTexture(GL_TEXTURE_2D,tex6);
        glDrawArrays(GL_TRIANGLES,12,6);
        glBindTexture(GL_TEXTURE_2D,tex2);
        glDrawArrays(GL_TRIANGLES,30,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)ygr.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)ygr.trans);
        glBindTexture(GL_TEXTURE_2D,tex4);
        glDrawArrays(GL_TRIANGLES,0,6);
        glBindTexture(GL_TEXTURE_2D,tex6);
        glDrawArrays(GL_TRIANGLES,12,6);
        glBindTexture(GL_TEXTURE_2D,tex2);
        glDrawArrays(GL_TRIANGLES,30,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)og.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)og.trans);
        glBindTexture(GL_TEXTURE_2D,tex3);
        glDrawArrays(GL_TRIANGLES,6,6);
        glBindTexture(GL_TEXTURE_2D,tex6);
        glDrawArrays(GL_TRIANGLES,12,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)g.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)g.trans);
        glBindTexture(GL_TEXTURE_2D,tex6);
        glDrawArrays(GL_TRIANGLES,12,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)gr.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)gr.trans);
        glBindTexture(GL_TEXTURE_2D,tex4);
        glDrawArrays(GL_TRIANGLES,0,6);
        glBindTexture(GL_TEXTURE_2D,tex6);
        glDrawArrays(GL_TRIANGLES,12,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)ogw.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)ogw.trans);
        glBindTexture(GL_TEXTURE_2D,tex3);
        glDrawArrays(GL_TRIANGLES,6,6);
        glBindTexture(GL_TEXTURE_2D,tex6);
        glDrawArrays(GL_TRIANGLES,12,6);
        glBindTexture(GL_TEXTURE_2D,tex5);
        glDrawArrays(GL_TRIANGLES,24,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)gw.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)gw.trans);
        glBindTexture(GL_TEXTURE_2D,tex6);
        glDrawArrays(GL_TRIANGLES,12,6);
        glBindTexture(GL_TEXTURE_2D,tex5);
        glDrawArrays(GL_TRIANGLES,24,6);

        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"),1,GL_FALSE,(float *)gwr.model);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"trans"),1,GL_FALSE,(float *)gwr.trans);
        glBindTexture(GL_TEXTURE_2D,tex4);
        glDrawArrays(GL_TRIANGLES,0,6);
        glBindTexture(GL_TEXTURE_2D,tex6);
        glDrawArrays(GL_TRIANGLES,12,6);
        glBindTexture(GL_TEXTURE_2D,tex5);
        glDrawArrays(GL_TRIANGLES,24,6);
        
        

        
        

        

        SDL_GL_SwapWindow(window);

        SDL_Delay(16);
    }
    

    return 0;
}

