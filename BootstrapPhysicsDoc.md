## 2D Physics

##### *This game uses [Bootstrap](https://github.com/AcademyOfInteractiveEntertainment/aieBootstrap)*

#### *Classes*
- [PhysicsGame](#class-PhysicsGame)
- [PhysicsObject](#class-PhysicsObject)
- [PhysicsScene](#class-PhysicsScene)
- [RigidBody](#class-RigidBody)
- [Plane](#class-Plane)
- [Sphere](#class-Sphere)

<br/>

| Enum ShapeType |
| -------------- |
| PLANE |
| SPHERE |
| BOX |
| LENGTH |

### Headers:

#### Class [PhysicsGame](PhysicsProject/PhysicsGame.h)

| Functions | Member class | Type | Description |
| --------- | ------------ | ---- | ----------- |
| PhysicsGame()  | public | PhysicsGame | Default Contructor |
| ~PhysicsGame() | public | PhysicsGame | Default Destructor |
| startup() | public (virtual) | bool | Creates Gizmos, renderer, and new scene when called |
| shutdown() | public (virtual) | void | Deletes renderer, scene, and font |
| update(float deltaTime) | public (virtual) | void | Updates scene every frame |
| draw() | public (virtual) | void | Draws the scene |

<br/>

#### Class [PhysicsObject](PhysicsProject/PhysicsObject.h)

| Functions | Member class | Type | Description |
| --------- | ------------ | ---- | ----------- |
| PhysicsObject(ShapeType shapeID) : m_shapeID(shapeID) | Protected | PhysicsObject | Default Contructor |
| fixedUpdate(glm::vec2 gravity, float timeStep) = 0 | public (pure virtual) | void | Used for physics in the scene |
| draw() = 0 | public (pure virtual) | void | Draws objects in the scene |
| resetPosition() | public (virtual) | void | Resets the position of the object |

<br/>

#### Class [PhysicsScene](PhysicsProject/PhysicsScene.h)

| Functions | Member class | Type | Description |
| --------- | ------------ | ---- | ----------- |
| PhysicsScene() | public | PhysicsScene | Default Contructor |
| ~PhysicsScene() | public | PhysicsScene | Default Destructor |
| addActor(PhysicsObject* actor) | public | void | Adds an actor to the scene |
| removeActor(PhysicsObject actor) | public | void | Removes an actor from the scene |
| removeAllActors() | public | void | Removes every actor in the scene |
| update(float deltaTime) | public | void | calculates the physics for each actor |
| draw() | public | void | Calls each actor's draw |
| checkCollision() | public | void | Checks if an object had a collision |
| planeToPlane(PhysicsObject* obj1, PhysicsObject* obj2) | public (static) | bool | Checks collision for Plane to Plane |
| planeToSphere(PhysicsObject* obj1, PhysicsObject* obj2) | public (static) | bool | Checks collision for Plane to Sphere |
| planeToBox(PhysicsObject* obj1, PhysicsObject* obj2) | public (static) | bool | Checks collision for Plane to Box |
| sphereToPlane(PhysicsObject* obj1, PhysicsObject* obj2) | public (static) | bool | Checks collision for Sphere to Plane |
| sphereToSphere(PhysicsObject* obj1, PhysicsObject* obj2) | public (static) | bool | Checks collision for Sphere to Sphere |
| sphereToBox(PhysicsObject* obj1, PhysicsObject* obj2) | public (static) | bool | Checks collision for Sphere to Box |
| boxToPlane(PhysicsObject* obj1, PhysicsObject* obj2) | public (static) | bool | Checks collision for Box to Plane |
| boxToSphere(PhysicsObject* obj1, PhysicsObject* obj2) | public (static) | bool | Checks collision for Box to Sphere |
| boxToBox(PhysicsObject* obj1, PhysicsObject* obj2) | public (static) | bool | Checks collision for Box to Box |

<br/>

#### Class [RigidBody](PhysicsProject/RigidBody.h)

| Functions | Member class | Type | Description |
| --------- | ------------ | ---- | ----------- |
| RigidBody(ShapeType shapeID, Vector2 pos, Vector2 velocity, float orientation, float mass) | public | RigidBody | Default Constructor |
| ~RigidBody() | public | RigidBody | Default Destructor |
| fixedUpdate(Vector2 gravity, float timeStep) | public (virtual) | void | Calculates physics for objects in the scene |
| applyForce(Vector2 force) | public | void | Applies a force to the RigidBody |
| applyForceToOther(RigidBody* other, Vector2 force) | public | void | Applies a force to the given RigidBody |
| resolveCollision(RigidBody* other) | public | void | Applies a force to the given RigidBody based on the collision. |
| getPosition() | public | Vector2 | Returns m_position |
| getVelocity() | public | Vector2 | Returns m_velocity |
| getOrientation() | public | float | Returns m_orientation |
| getMass() | public | float | Returns m_mass |

<br/>

#### Class [Plane](PhysicsProject/Plane.h)

| Functions | Member class | Type | Description |
| --------- | ------------ | ---- | ----------- |
| Plane(Vector2 normal, float distance, Vector4 color) | public | Plane | Default Contructor |
| ~Plane() | public | Plane | Default Destructor |
| fixedUpdate(Vector2 gravity, float timeStep) | public (virtual) | void |  |
| draw() | public (virtual) | void | Draws a plane to the scene |
| resolveCollision(RigidBody* other) | public | void | Applies a force to the given RigidBody based on the collision |
| getNormal() | public | Vector2 | Returns m_normal |
| getDistance() | public | float | Returns m_distance |
| getColor() | public | Vector4 | Returns m_color |

<br/>

#### Class [Sphere](PhysicsProject/Sphere.h)

| Functions | Member class | Type | Description |
| --------- | ------------ | ---- | ----------- |
| Sphere(Vector2 position, Vector2 velocity, float mass, float radius, Vector4 color) | public | Sphere | Default Contructor |
| ~Sphere() | public | Sphere | Default Destructor |
| draw() | public (virtual) | void | Draws a Sphere to the scene |
| getRadius() | public | float | Returns m_radius |
| getColor() | public | Vector4 | Returns m_color |