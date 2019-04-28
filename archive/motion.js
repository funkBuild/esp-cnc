const constraints = {
  v: 250,
  a: 1000,
  j: 100000
};

function distance_until_velocity_reached(v_initial, max_velocity){
  let t = (constraints.j*max_velocity - Math.pow(constraints.a,2) - constraints.j*v_initial) / (constraints.j*constraints.a)
  console.log(t);

  let term1 = Math.pow(constraints.a, 3) / Math.pow(constraints.j,2)
  let term2 = (3 * Math.pow(constraints.a, 2) * t) / (2*constraints.j);
  let term3 = (constraints.a * Math.pow(t, 2)) / 2;
  let term4 = (2 * constraints.a * v_initial) / constraints.j;
  let term5 = t * v_initial;

  return {
    d: term1 + term2 + term3 + term4 + term5,
    t
  }
}

let blocks = [
  {max_entry_speed: 0, programmed_speed: 200, distance: 100},
  {max_entry_speed: 0, programmed_speed: 200, distance: 100}
];



console.log(distance_until_velocity_reached(5, 11));



for(let i = blocks.length-1; i >= 0; i--){
  let block = blocks[i];
  let nextBlock = blocks[i+1];

  let max_exit_speed = 0;


  if(nextBlock){
    max_exit_speed = nextBlock.max_entry_speed;
  }
  
  let decellProfile = distance_until_velocity_reached(
    max_exit_speed,
    Math.min(constraints.v, block.programmed_speed)
  )

  block.max_entry_speed = decellProfile.d
  console.dir(decellProfile);
}


/*

total time to react distance give a starting velocity

  t= −3a2−2jvi+√a4−4a2jvi+8aj2sc+4j2vi2 2aj
  t=− 3a2+2jvi+√a4−4a2jvi+8aj2sc+4j2vi2 2aj ; j≠ 0


*/
