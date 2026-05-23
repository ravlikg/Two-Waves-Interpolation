#version 110

uniform float t;
uniform float amp1;
uniform float freq1;
uniform float amp2;
uniform float freq2;
uniform vec2 source1;
uniform vec2 source2;

void main() {
    //текущий пиксель
    vec2 pixelPos = gl_FragCoord.xy;

    //расстояние к источникам
    float r1 = distance(pixelPos, source1);
    float r2 = distance(pixelPos, source2);

    //Формула волн
    float wave1 = amp1 * sin(r1 * freq1 - t);
    float wave2 = amp2 * sin(r2 * freq2 - t);
    float totalWave = wave1 + wave2;

    //Покраска волны
    vec4 color = vec4(0.0, 0.0, 0.0, 1.0);//чорный

    if (totalWave > 0.0) {
        //синий гребень
        color.g = min(1.0, totalWave * 0.003);
        color.b = min(1.0, totalWave * 0.03);
    } else {
        //красный впадина
        color.r = min(1.0, -totalWave * 0.03);
    }
    gl_FragColor = color;
}