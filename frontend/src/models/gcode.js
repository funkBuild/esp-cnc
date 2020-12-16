class Point {
  constructor(x, y, z){
    this.x = x;
    this.y = y;
    this.z = z;
  }

  clone(){
    return new Point(this.x, this.y, this.z);
  }
}

class Line {
  constructor(start, end, isExtruded){
    this.start = start;
    this.end = end;
    this.isExtruded = isExtruded;
  }
}

class GcodeFile {
  constructor(text){
    this.text = text;
  }

  toLines(){
    let gcodeLines = this.text.split('\n');
    let currentPosition = new Point(0, 0, 0);
    let extruderPosition = 0;
    let lines = [];

    gcodeLines.forEach( line => {
      line = line.trim();
      
      if(line[0] != 'G') return;

      let parts = line.split(' ');
      let command = {position: {}, isExtruded: false};


      parts.forEach( part => {
        let posValue = Number(part.slice(1));

        switch(part[0]){
          case 'G':
            command.type = 'G';
            command.code = posValue;
            break;
          case 'E':
            command.isExtruded = extruderPosition < posValue;
            extruderPosition = posValue;
          case 'X':
          case 'Y':
          case 'Z':
            command.position[part[0]] = posValue;
            break;
        }
      });

      if(command.type == 'G' && command.code == 1){
        let startPoint = currentPosition.clone();
        
        if(command.position.X) currentPosition.x = command.position.X;
        if(command.position.Y) currentPosition.y = command.position.Y;
        if(command.position.Z) currentPosition.z = command.position.Z;

        let endPoint = currentPosition.clone();
        let newLine = new Line(startPoint, endPoint, command.isExtruded);

        //console.log(line);
        //console.dir(newLine);

        lines.push( newLine );

      };

    });
    return lines;
  }

  toGcodeLines(){
    return this.text.split('\n').filter(line => line.length > 0);
  }
}

export default GcodeFile;
