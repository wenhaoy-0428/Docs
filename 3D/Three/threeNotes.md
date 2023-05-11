# React Three Fiber

### Workflow

1. All the 3D scenes are fit inside a `canvas`. To abstract many of the settings that required to setup a Three.js scene, R3F, put all of them inside a `Canvas` component. A detail setup using Three.js can be found at [Three.js Crash Course For Beginners | Create This Awesome 3D Website!](https://www.youtube.com/watch?v=_OwJV2xL8M8).

```js
import ReactDOM from 'react-dom'
import { Canvas } from '@react-three/fiber'

function App() {
  return (
    <div id="canvas-container">
      <Canvas />
    </div>
  )
}

ReactDOM.render(<App />, document.getElementById('root'))
```

> Canvas is responsive to fit the parent node, so you can control how big it is by changing the parents width and height, in this case #canvas-container.

2. Since, R3F can be treated as an additional layer that makes three.js self-contained in a React way, we are only dealing with 1 three.js scene even we wrapped them in a nested way. The result of this is that we can access the scene through any components and we can set the lighting, the camera inside any custom components. For example to add orbit control to our scene, we can implement a `orbitcontolmanager` component.


```js
  function OrbitController() {
    const { camera, gl } = useThree();
    useEffect(() => {
      const controls = new OrbitControls(camera, gl.domElement);
      // controls.minDistance = 3;
      // controls.maxDistance = 20;
      return () => {
        controls.dispose();
      };
    }, [camera, gl]);
  }

  const cameraRef = useRef();

  return (
    <div className="w-full h-full">
      <Canvas>
        <Suspense fallback={null}>
          <OrbitController />

          {/* <CameraController /> */}

          <ambientLight />
          <pointLight position={[0, 10, 10]} />
          {/* <Box position={[-1.2, 0, 0]} /> */}
          {/* <Box position={[1.2, 0, 0]} /> */}
          <Model />
        </Suspense>
      </Canvas>
    </div>
  );
```

3. The same is true for cameras, we can have a `cameraManager` component



### [Import 3D models/scene into](https://docs.pmnd.rs/react-three-fiber/tutorials/loading-models#loading-gltf-models)

Three.js support many formats of 3D models. GLTF format is one of the mostly used. 

```js
import { useLoader } from '@react-three/fiber'
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader'


function Scene() {
  const gltf = useLoader(GLTFLoader, '/Poimandres.gltf')
  return <primitive object={gltf.scene} />
}
```

In the above code [primitive](https://docs.pmnd.rs/react-three-fiber/api/objects#putting-already-existing-objects-into-the-scene-graph) is a placeholder that allows to add existing objects. 

Note, it's likely that you'll have an error `A component suspended while responding to synchronous input` reported when using useLoader. //TODO: REASON 

To solve this, add wrap the functional component with a `Suspense`.

```js

  function Model({ setCamera }) {
    const gltf = useLoader(GLTFLoader, "/TrophyCard.glb");

    return (
      <>
        <primitive object={gltf.scene} scale={0.3} />;
      </>
    );
  }

  const cameraRef = useRef();

  return (
    <div className="w-full h-full">
    
      <Canvas>
      <Suspense fallback={null}>
        <OrbitController />
        <ambientLight />
        <pointLight position={[0, 10, 10]} />
        <Model />
        </Suspense>
      </Canvas>
    </div>
    
```

#### Custom imported model/scene

We use `useLoader` of R3F hook to load the gltf files. The return value is an object that contains everything the model has, and it also has a `Children` property inside `scene` that contains all the nodes of the model. 

> Children is a hierarchy tree containing all the geometries and relations, also only leaves are geometries.

To quickly edit them, we can traverse the children, or use children name to select.

```js
gltf.scene.traverse( child => {
    if ( child.material ) child.material.metalness = 0;
} );
```

Alternatively, an exciting feature `useLoader` offers is that when the result of useLoader contains `result.scene` property, `useLoader` will automatically return `{nodes, material}` where nodes is a hierarchy tree contains all the geometries and `materials` contains all the materials. Thus, we can build immutable scene graphs selectively. You can also specifically alter the data without having to traverse it. And this time, we have to assemble our model ourselves.

```js

  function Model({ setCamera }) {
    const { nodes, materials } = useLoader(GLTFLoader, "/TrophyCard.glb");
    return (
      <>
        <Stage
          adjustCamera={1.5}
          intensity={0.5}
          shadows="accumulative"
          environment={{
            files: "/kloofendal_48d_partly_cloudy_puresky_4k.hdr"
          }}
        >
          <group scale={0.3} dispose={null}>
            <group rotation={[Math.PI / 2, 0, 0]} scale={[2.5, 0.1, 2.5]}>
              <mesh
                castShadow
                receiveShadow
                geometry={nodes.TrophyCard_1.geometry}
                material={materials.MainMetal}
              />
              <mesh
                castShadow
                receiveShadow
                geometry={nodes.TrophyCard_2.geometry}
                material={materials.bevelMetal}
              />
              <mesh
                castShadow
                receiveShadow
                geometry={nodes.TrophyCard_3.geometry}
                material={materials.RoughMedal}
              />
              <mesh
                castShadow
                receiveShadow
                geometry={nodes.TrophyCard_4.geometry}
                material={materials.LarualMaterial}
              />
            </group>
          </group>
        </Stage>
      </>
    );
  }

```

This also gives us so much more flexibility. Due the fact that it is error prone to assemble models ourselves. Official docs of [Loading GLTF models as JSX Components](https://docs.pmnd.rs/react-three-fiber/tutorials/loading-models#loading-gltf-models-as-jsx-components) provides us **a tool to convert gltf file to the above code** for us using [https://gltf.pmnd.rs/](https://gltf.pmnd.rs/).


### [Enable OrbitControl in ReactThreeFiber](https://www.tutorialspoint.com/adding-orbitcontrols-in-react-using-reactthree-fiber)




### Issue of imported objects that look too dark

In three.js, we have serval types of lighting, a reference can be found at this video [Three.js Lighting Tutorial with Examples](https://www.youtube.com/watch?v=bsLosbweLNE). `AmbientLight` is very essential as it will light up the objects evenly from all angles. However, due to the design of three.js. **Fully metallic surfaces doesn't work with ambient lights**, they only work with lights that are directional, so that physical reflection can be applied. 

[This is just how metallic reflectance works — it isn’t a bug, and there is no workaround. A reflective metallic surface needs details to reflect, and ambient and directional lights do not provide that. The reflected image comes from an environment map, which can be baked or generated at runtime.](https://discourse.threejs.org/t/solved-glb-model-is-very-dark/6258/7)

More reference can be found at [How to use GLTF Loader in three.js? Texture and material displaying as black](https://stackoverflow.com/questions/53344348/how-to-use-gltf-loader-in-three-js-texture-and-material-displaying-as-black/53349297#53349297)


Also, the material imported from the gltf are commonly [MeshPhysicalMaterial](https://threejs.org/docs/index.html#api/en/materials/MeshPhysicalMaterial). According to the official docs, `MeshPhysicalMaterial has a higher performance cost, per pixel, than other three.js materials. Most effects are disabled by default, and add cost as they are enabled. For best results, always specify an environment map when using this material.`

Therefore, we can add `envMap` to materials so that they look properly. Steps of setting up envMap can be found at [set envMap](#set-envmap)


### Set envMap

> One of the most popular websites that is free to download environment file is [Poly Haven](https://polyhaven.com). 

In three.js, a setup reference can be found at this video [Three.js Realistic Material Reflection Tutorial in 8 Minutes](https://www.youtube.com/watch?v=aJun0Q0CG_A). 


For react three fiber, it can be much easier. A step by step video can be found at [Generated Environment Maps in React Three Fiber and Three.js](https://www.youtube.com/watch?v=15vSOupAyqk&t=320s).

```js
import { useEnvironment } from "@react-three/drei";
const envMap = useEnvironment({
    files: "/kloofendal_48d_partly_cloudy_puresky_4k.hdr",
});

mesh.material.envMap = envMap;
```

Also, [React Three Drei](https://github.com/pmndrs/drei) provides many methods to ease our life. We can also wrap meshes inside [Environment](https://github.com/pmndrs/drei#environment) component and provide path in `files` prop of `<Environment>`.


> Note: in react three fiber files use relative path inside `public` folder, so that the above path points to `../public/kloo...hdr`

Refer to [custom imported models](#custom-imported-modelscene) for steps to add envMap to imported models.



https://github.com/KhronosGroup/glTF-Blender-IO/issues/240






    




