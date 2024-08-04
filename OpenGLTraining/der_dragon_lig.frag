#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
//in vec4 LightSpacePos;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D gDepth;
uniform sampler2D sDepth;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform mat4 lightspacematrix;

uniform float metallic;
uniform float roughness;
uniform float ao;

const float PI = 3.14159265359;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(sDepth, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = 0.005;
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    if(currentDepth > 1.0)
        shadow = 0.0;
    return shadow;
}

vec3 freselSchlick(float cosTheta, vec3 F0)
{
    return F0 + (vec3(1.0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

void main()
{             
    if(texture(gDepth, TexCoords).r == 1.0f)
        discard;
    // retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;

    vec3 N = Normal;
    vec3 V = normalize(cameraPosition - FragPos);
    vec3 L = normalize(lightPosition - FragPos);
    vec3 H = normalize(V + L);
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, Diffuse, metallic);
    vec3 F = freselSchlick(max(dot(H, L), 0.0), F0);
    float distance = length(FragPos - lightPosition);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = lightColor * attenuation;

    float NDF = DistributionGGX(Normal, H, roughness);
    float G = GeometrySmith(Normal, V, L, roughness);
    vec3 nominator = F * NDF * G;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001;
    vec3 BRDF = nominator / denominator;

    vec3 Ks = F;
    vec3 Kd = vec3(1.0) - Ks;
    Kd *= 1.0 - metallic;

    vec3 Lo = vec3(0.0);
    float NdotL = max(dot(N, L), 0.0);
    Lo += (Kd * Diffuse / PI + BRDF) * radiance * NdotL;

    vec3 ambient = vec3(0.03) * Diffuse *ao;
    
    float shadow = ShadowCalculation(lightspacematrix * vec4(FragPos, 1.0));
    vec3 color = (ambient + (1 - shadow)) * Lo;
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));

    
    

    FragColor = vec4(color, 1.0);


    
    // // then calculate lighting as usual
    // vec3 lighting  = Diffuse * 0.1; // hard-coded ambient component
    // // diffuse
    // vec3 lightDir = normalize(lightPosition - FragPos);
    // float diff = max(dot(Normal, lightDir), 0.0);
    // vec3 diffuse = diff * lightColor;
    // // specular
    // vec3 viewDir = normalize(cameraPosition - FragPos);
    // vec3 reflectDir = reflect(-lightDir, Normal);  
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    // vec3 specular = Specular * spec * lightColor;  
    // // calculate shadow
    // float shadow = ShadowCalculation(lightspacematrix * vec4(FragPos, 1.0));
    // lighting = (lighting + (1 - shadow)) * (diffuse + specular);       
    // FragColor = vec4(lighting, 1.0);
}
