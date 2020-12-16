import React, { Component } from 'react';
import * as THREE from 'three';
import OrbitControlsImport from 'three-orbit-controls';

import State from '../models/state';
import Device from '../models/Device';
import '../style/ThreeDisplay.css';

const OrbitControls = OrbitControlsImport(THREE);


class ThreeDisplay extends Component {
  constructor(props) {
    super(props)

    this.start = this.start.bind(this)
    this.stop = this.stop.bind(this)
    this.animate = this.animate.bind(this)
  }

  componentDidMount() {
    window.addEventListener("resize", this.updateDimensions.bind(this));

    const height = this.container.clientHeight;
    const width = this.container.clientWidth;

    const scene = new THREE.Scene()

    let aspect = width / height;
    let d = 100;
    const camera = new THREE.OrthographicCamera( - d * aspect, d * aspect, d, - d, 1, 50000 );


    camera.position.set( -500, 500, -500 );
    camera.lookAt( new THREE.Vector3( 0, 0, 0 ) );


    this.controls = new OrbitControls(camera)

    //camera.position.set( 3, 3, 3 ); // all components equal
    //camera.lookAt( scene.position ); // or the origin

    const renderer = new THREE.WebGLRenderer({ canvas: this.canvas, antialias: true })
    const geometry = new THREE.BoxGeometry(1, 1, 1)
    const material = new THREE.MeshNormalMaterial({})

    renderer.setClearColor('#000000')

    scene.background = new THREE.Color( 0xffffff );

    this.scene = scene
    this.camera = camera
    this.renderer = renderer
    this.material = material

    this.start()

    this.drawGrid();
    this.drawAxisLines();

    renderer.setSize(width, height)

    State.on('modelLines', this.drawLines.bind(this));
    Device.on("positionUpdated", () => this.drawMarker());
  }

  componentWillUnmount() {
    this.stop()
    this.mount.removeChild(this.renderer.domElement)
    window.removeEventListener("resize", this.updateDimensions.bind(this));
  }

  updateDimensions(){
    const height = this.container.clientHeight;
    const width = this.container.clientWidth;

    this.camera.aspect = width / height; //window.innerWidth / window.innerHeight;
    this.camera.updateProjectionMatrix();

    this.renderer.setSize( width, height); //window.innerWidth, window.innerHeight );
  }

  start() {
    if (!this.frameId) {
      this.frameId = requestAnimationFrame(this.animate)
    }
  }

  stop() {
    cancelAnimationFrame(this.frameId)
  }

  animate() {
    this.renderScene()
    this.frameId = window.requestAnimationFrame(this.animate)
  }

  renderScene() {
    this.renderer.render(this.scene, this.camera)
  }

  drawLines(lines){
    let extrudedGroup = new THREE.Group();
    let rapidGroup = new THREE.Group();

    let extrudedMaterial = new THREE.LineBasicMaterial({color: 0x0000ff, opacity: 0.2,
					  transparent: true,
					  linewidth: 1,});
    let rapidMaterial = new THREE.LineBasicMaterial({color: 0x000000});

    let geometry, isExtruded;

    for(let i = 0; i < lines.length; i++){
      let line = lines[i];
      //console.dir(line);

      if(!geometry) {
        geometry = new THREE.Geometry();
        isExtruded = line.isExtruded;

        geometry.vertices.push(
	        new THREE.Vector3(line.start.y, line.start.z, line.start.x)
        );
      }

      geometry.vertices.push(
        new THREE.Vector3(line.end.y, line.end.z, line.end.x)
      );

      if(lines[i+1] && lines[i+1].isExtruded != isExtruded) {
        let threeLine = new THREE.Line( geometry, isExtruded ? extrudedMaterial : rapidMaterial );

        if(isExtruded)
          extrudedGroup.add(threeLine);
        else
          rapidGroup.add(threeLine);

        geometry = null;
      }
    };

    this.scene.add( extrudedGroup );
  }

  drawAxisLines(){
    const xMaterial = new THREE.LineBasicMaterial( { color: 0x00ff00 } );
    const yMaterial = new THREE.LineBasicMaterial( { color: 0xff0000 } );
    const zMaterial = new THREE.LineBasicMaterial( { color: 0x0000ff } );
    const xGeometry = new THREE.Geometry(), yGeometry = new THREE.Geometry(), zGeometry = new THREE.Geometry();

    xGeometry.vertices.push(new THREE.Vector3( 0, 0, 0) );
    xGeometry.vertices.push(new THREE.Vector3( 200, 0, 0) );

    yGeometry.vertices.push(new THREE.Vector3( 0, 0, 0) );
    yGeometry.vertices.push(new THREE.Vector3( 0, 0, 200) );

    zGeometry.vertices.push(new THREE.Vector3( 0, 0, 0) );
    zGeometry.vertices.push(new THREE.Vector3( 0, 200, 0) );

    this.scene.add(new THREE.Line( xGeometry, xMaterial ));
    this.scene.add(new THREE.Line( yGeometry, yMaterial ));
    this.scene.add(new THREE.Line( zGeometry, zMaterial ));
  }

  drawGrid(){
    var material = new THREE.LineBasicMaterial( { color: 0x444444 } );
    var xGeometry = new THREE.Geometry();

    for(let i=0; i < 20; i++){
      xGeometry.vertices.push(new THREE.Vector3(10*i, 0, 0) );
      xGeometry.vertices.push(new THREE.Vector3(10*i, 0, 200) );
      xGeometry.vertices.push(new THREE.Vector3(10*i+10, 0, 200) );
    }

    let xLine = new THREE.Line( xGeometry, material );
    this.scene.add( xLine );
    var yGeometry = new THREE.Geometry();

    for(let i=0; i < 20; i++){
      yGeometry.vertices.push(new THREE.Vector3(0, 0, 10*i) );
      yGeometry.vertices.push(new THREE.Vector3(200, 0, 10*i) );
      yGeometry.vertices.push(new THREE.Vector3(200, 0, 10*i+10) );
    }

    let yLine = new THREE.Line( yGeometry, material );
    this.scene.add( yLine );
  }

  drawMarker(){
    if(!this.marker){
      let geometry = new THREE.ConeGeometry( 5, 20, 32 );
      let material = new THREE.MeshBasicMaterial( {color: 0xffff00} );
      this.marker = new THREE.Mesh( geometry, material );

      this.marker.rotateZ(Math.PI);
      this.marker.geometry.computeBoundingBox();
      this.marker.geometry.translate(0, -10, 0);

      this.scene.add( this.marker );
    }

    this.marker.position.x = Device.state.position.y;
    this.marker.position.y = Device.state.position.z;
    this.marker.position.z = Device.state.position.x;

  }

  render() {
    return (
      <div className="ThreeContainer" ref={ref => { this.container = ref }}>
        <canvas
          ref={ref => { this.canvas = ref }}
        />
      </div>
    )
  }
}

export default ThreeDisplay;
