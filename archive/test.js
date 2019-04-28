
let j = 100;
let a = 10;
let v = 11;

let v_initial = 0;

let t_a = a/j;
let t_b = 1

let t = (j*v - Math.pow(a,2) - j*v_initial) / (j*a)
console.log(`t_b_calc=${t}`);

let a_a = a; //j*t_a;
let v_a = v_initial + (a*a)/(2 * j);
//let s_a = v_initial * t_a + j * Math.pow(t_a, 3) / 6;
let s_a = (v_initial * a) / j + Math.pow(a,3) / (6*Math.pow(j,2))


console.log(`t_a=${t_a}`);
console.log(`v_a=${v_a}`);
console.log(`a_a=${a_a}`);
console.log(`s_a=${s_a}`);
console.log('');

let a_b = a_a;
let v_b = v_a + a_b * t_b;
//v_b = (2*j*v-2*j*v_initial-Math.pow(a,2))/(2*j)+v_initial
v_b=(2*j*v-Math.pow(a,2))/(2*j)
let s_b = s_a + v_a * t_b + 0.5 * a_b * Math.pow(t_b, 2);

console.log(`a_b=${a_b}`);
console.log(`v_b=${v_b}`);
console.log(`s_b=${s_b}`);
console.log('');

let a_c = a_b - j*t_a;
let v_c = v_b + (a*a)/(2*j);
let s_c = s_b + v_b * t_a + Math.pow(a,3) / (3*Math.pow(j,2)) 
//0.5 * a * Math.pow(t_a, 2) - j * Math.pow(t_a, 3) / 6;

console.log(`a_c=${a_c}`);
console.log(`v_c=${v_c}`);
console.log(`s_c=${s_c}`);




let t_step = 1/600000;

let a_cur=0;
let v_cur=v_initial;
let s_cur=0;

for(let t=0; t <= 2*t_a + t_b; t += t_step){
  if(t < t_a){
    // accell
    a_cur += t_step * j;
  } else if(t < t_a+t_b){

  } else {
    // decell
    a_cur -= t_step * j;
  }

  v_cur += t_step * a_cur;
  s_cur += t_step * v_cur;
}
console.log('\nSimulation');
console.log(`a_b=${a_cur}`);
console.log(`v_b=${v_cur}`);
console.log(`s_b=${s_cur}`);


console.log('\ncomputed direct');

let c_v_c = a*a/j + a*t_b + v_initial
console.log(`v_c=${v_c}`);

/*

t_b = \frac{\left(v\cdot \:j-a^2-j\cdot \:v_i\right)}{a\cdot \:j}
s_a = v_i\cdot \frac{a}{j}+\frac{a^3}{6j}
v_a= v_i\cdot +\frac{a^2}{2\cdot j}

s_b = (3 * j * v^2 - 3 * a^3 * v + 3*a^2*v_i - 3 * j * v_i^3 + a^4) / 6*a*j;
v_b = (2*j*v - a^2) / 2*j


v_i\cdot \frac{a}{j}+\frac{a^3}{6\cdot \:j^2}+t_b\cdot \left(v_i+\frac{a^2}{2\cdot \:j}\right)\:+\:\frac{a\cdot \:t_{b^2}}{2}+a\cdot \left(\frac{a}{j}\right)-\frac{j\cdot \left(\frac{a}{j}\right)^2}{2}
*/

