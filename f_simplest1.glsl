#version 330


struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


uniform sampler2D textureMap0;
uniform sampler2D textureMap1;

uniform vec3 cam_pos;

//Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela
out vec4 pixelColor; 

in vec2 iTexCoord0;
in vec3 FragPos;
in vec3 newNormal;


PointLight lp1 = PointLight(vec3(2.0f, 25.0f, 2.0f), 20.0f, 0.00001f, 0.00001f, vec3(1.0f), vec3(1.0f), vec3(1.0f));
PointLight lp2 = PointLight(vec3(25.0f, 10.0f, 25.0f), 1.0f, 0.09f, 0.032f, vec3(.7f), vec3(.6f), vec3(.8f));
PointLight lp3 = PointLight(vec3(25.0f, 10.0f, 0.0f), 1.0f, 0.09f, 0.032f, vec3(.7f), vec3(.6f), vec3(.8f));
PointLight lp4 = PointLight(vec3(0.0f, 10.0f, -25.0f), 1.0f, 0.09f, 0.032f, vec3(.7f), vec3(.6f), vec3(.8f));



vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 tex, vec3 tex_2nd) {
    vec3 lightDir = normalize(light.position - fragPos);
    
    // matowe œwiat³o xD
    float diff = max(dot(normal, lightDir), 0.0);
    
    // phong œwiat³o
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 100);
    
    //os³abienie
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    vec3 ambient = light.ambient * tex;
    vec3 diffuse = light.diffuse * diff * tex;
    vec3 specular = light.specular * spec  * tex * tex_2nd;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return 4*(ambient + diffuse + specular);
}


void main(void) {
    vec3 tex = vec3(texture(textureMap0, iTexCoord0));
    vec3 tex_2nd = vec3(texture(textureMap1, iTexCoord0));
    vec3 viewDir = normalize(10*cam_pos - FragPos);
    vec3 norm = normalize(newNormal.xyz);

    vec3 result = vec3(0.0f);
    result += CalcPointLight(lp1, norm, FragPos, viewDir, tex, tex_2nd);
    result += CalcPointLight(lp2, norm, FragPos, viewDir, tex, tex_2nd);
    result += CalcPointLight(lp3, norm, FragPos, viewDir, tex, tex_2nd);
    result += CalcPointLight(lp4, norm, FragPos, viewDir, tex, tex_2nd);

    pixelColor = vec4(vec3(1.0) - exp(-result * 1.0f), 1.0);
}


