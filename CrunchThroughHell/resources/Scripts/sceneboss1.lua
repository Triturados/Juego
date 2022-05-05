
local sceneboss1 = {}

function sceneboss1:createCharco(name, type, x,y,z)
    local charco = scene:createObject(name);

    local tr = charco:addComponent("Transform");

    tr:sendMsg([[
        scale: 10,1,10;
        position: ]] .. x .. [[ , ]] .. y .. [[ , ]] .. z .. [[;
        rotation: 0,0,0;
    ]])

    charco:addComponent("Mesh"):sendMsg([[
        meshName: ]] .. name .. [[.mesh;
    ]])

    charco:addComponent('Rigidbody'):sendMsg([[
        trigger: true;
        mass: 0.0;
        shape: cube;
        restitution: 0.9;
        colliderScale:10,1,10;
    ]])

    charco:addComponent('EfectoEscenario'):sendMsg([[
        type: ]] .. type .. [[
    ]])

    return tr;

end

function sceneboss1:createMesh(meshName, x,y,z, sx, sy, sz, rx, ry, rz)
    local mesh = scene:createObject(meshName);

    local tr = mesh:addComponent("Transform");

    tr:sendMsg([[
        scale: ]] .. sx .. [[ , ]] .. sy .. [[ , ]] .. sz .. [[;
        position: ]] .. x .. [[ , ]] .. y .. [[ , ]] .. z .. [[;
        rotation: ]] .. rx .. [[ , ]] .. ry .. [[ , ]] .. rz .. [[;
    ]])

    mesh:addComponent("Mesh"):sendMsg([[
        meshName: ]] .. meshName .. [[;
    ]])

    return mesh;

end

function sceneboss1:createRigidMesh(meshName, x,y,z, sx, sy, sz, rx, ry, rz)
    local mesh = scene:createObject(meshName);

    local tr = mesh:addComponent("Transform");

    tr:sendMsg([[
        scale: ]] .. sx .. [[ , ]] .. sy .. [[ , ]] .. sz .. [[;
        position: ]] .. x .. [[ , ]] .. y .. [[ , ]] .. z .. [[;
        rotation: ]] .. rx .. [[ , ]] .. ry .. [[ , ]] .. rz .. [[;
    ]])

    mesh:addComponent("Mesh"):sendMsg([[
        meshName: ]] .. meshName .. [[;
    ]])

    mesh:addComponent('Rigidbody'):sendMsg([[
        mass: 0.0;
        state: static;
        shape: cube;
        restitution: 0.9;
        colliderScale: 14,25,14;
    ]])

    return mesh;

end

function sceneboss1:createSmoke(name, x,y,z)
    local particleSys = scene:createObject(name)
    local particleSystr = particleSys:addComponent("Transform"):sendMsg([[
        scale: 1,1,1;
        position: ]] .. x .. [[ , ]] .. y .. [[ , ]] .. z .. [[;
        rotation: 0,0,0;
        ]])
    local pSys = particleSys:addComponent("ParticleSystem")
    pSys:sendMsg([[particleName: bomb; emitting: true]])

    return particleSystr;

end

function sceneboss1:createScene() -- Boss1
    scene:name("Escena de Prueba")

    persistentObject:addComponent("ComponenteDeContar")

    local a = scene:createObject("AAA");
    a:addComponent("MoverPantalla"):sendMsg("inicial: 0.1")

    local testImagen = scene:createObject("uiobj")
    testImagen:addComponent("Transform")
    testImagen:addComponent("Image"):sendMsg([[
        material: ui
    ]])

    -- Limites mundo --
    --MURO1
    local muro1 = scene:createObject("muro1")
    local muroTr1 = muro1:addComponent("Transform")

    muroTr1:sendMsg([[
        scale: 1,10,150;
        position: -150,10,0;
        rotation: 0,0,0;
    ]])

    local rBMuro1 = muro1:addComponent('Rigidbody')
    rBMuro1:sendMsg([[
        trigger: false;
        state: kinematic;
        mass: 0.0;
        shape: cube;
        restitution: 0.9;
        colliderScale: 10,30,150;
    ]])
    --MURO2
    local muro2 = scene:createObject("muro2")
    local muroTr2 = muro2:addComponent("Transform")

    muroTr2:sendMsg([[
        scale: 1,10,150;
        position: 150,10,0;
        rotation: 0,0,0;
    ]])

    local rBMuro2 = muro2:addComponent('Rigidbody')
    rBMuro2:sendMsg([[
        trigger: false;
        state: kinematic;
        mass: 0.0;
        shape: cube;
        restitution: 0.9;
        colliderScale: 10,30,150;
    ]])

    --MURO3
    local muro3 = scene:createObject("muro3")
    local muroTr3 = muro3:addComponent("Transform")

    muroTr3:sendMsg([[
        scale: 150,10,1;
        position: 0,10,-150;
        rotation: 0,0,0;
    ]])

    local rBMuro3 = muro3:addComponent('Rigidbody')
    rBMuro3:sendMsg([[
        trigger: false;
        state: kinematic;
        mass: 0.0;
        shape: cube;
        restitution: 0.9;
        colliderScale: 150,30,10;
    ]])

    local muro4 = scene:createObject("muro4")
    local muroTr4 = muro4:addComponent("Transform")

    muroTr4:sendMsg([[
        scale: 150,10,1;
        position: 0,10,150;
        rotation: 0,0,0;
    ]])

    local rBMuro4 = muro4:addComponent('Rigidbody')
    rBMuro4:sendMsg([[
        trigger: false;
        state: kinematic;
        mass: 0.0;
        shape: cube;
        restitution: 0.9;
        colliderScale: 150,30,10;
    ]])

    -- Suelo--
    local suelo = scene:createObject("Suelo")
    local sueloTr = suelo:addComponent("Transform")

    -- Colocamos sus hijos
    local charcoTr = sceneboss1:createCharco("Charco", 0, 0,2,70)
    local charcoTr2 = sceneboss1:createCharco("Charco", 0, -70,2, -70)
    local charcoTr3 =  sceneboss1:createCharco("Charco", 0, 70,2,-70)

    -- Colocamos el padre
    sueloTr:sendMsg([[
        scale: 150,1,150;
        position: 0,-4,0;
        rotation: 0,0,0;
    ]])

    charcoTr:sendComponent(1, sueloTr)
    charcoTr2:sendComponent(1, sueloTr)
    charcoTr3:sendComponent(1, sueloTr)

     --------------------------------------------
    -- hijosmuros --
    muroTr1:sendComponent(1,sueloTr)
    muroTr2:sendComponent(1,sueloTr)
    muroTr3:sendComponent(1,sueloTr)
    muroTr4:sendComponent(1,sueloTr)
    ------------------------------

    local comp3 = suelo:addComponent("Mesh")
    comp3:sendMsg([[
        meshName: cube.mesh;
    ]])
    local compRigidbodySuelo = suelo:addComponent('Rigidbody')
    compRigidbodySuelo:sendMsg([[
        trigger: false;
        state: kinematic;
        mass: 0.0;
        shape: cube;
        restitution: 0.9;
        colliderScale: 150,3.5,150;
        ]])

    local material = suelo:addComponent("Material")
    material:sendMsg([[materialName: Hell_scenario]])
    material:sendComponent(0, comp3)

    local luz = scene:createObject("Luz")
    local compLuz = luz:addComponent('Transform')

    compLuz:sendMsg([[
        scale: 1,1,1;
        position: 0,40,0;
        rotation: -45,0,0;
    ]])

    local compLight = luz:addComponent('Light')
    compLight:sendMssg([[
        name: luz_direccional
        type: directional
    ]])
    ----------hijo ogro
    local bolaHijaJug = scene:createObject("BolaHija")
    local compTrBolaHijaJug = bolaHijaJug:addComponent('Transform')

    compTrBolaHijaJug:sendMsg([[
        scale: 0.02,0.02,0.02;
        position: 0,10,0;
        rotation: 0,0,0;
    ]])
    local compbolaHijaJugMesh = bolaHijaJug:addComponent('Mesh'):sendMsg([[
        meshName: sphere.mesh;
    ]])

    local rotarcam = bolaHijaJug:addComponent('CamRotate')
    --------------

    ----------bola hijo ogro "cam"
    local cam = scene:createObject("cam")
    local trcam = cam:addComponent('Transform')

    trcam:sendMsg([[
        scale: 2,2,2;
        position: 0,20,60;
        rotation: 0,0,0;
    ]])

    local camCamera = cam:addComponent('Camera')
    local camFollow = cam:addComponent('CamFollow')

    camCamera:sendMsg([[
        name: escenaJuego;
        zOrder: 2;
    ]])
    camCamera:sendMsg([[
        compositor: Posterize;
    ]])

    -- player--

    local playerSpawnHeight = 16
    local player = scene:createObject("jugador")
    local tr = player:addComponent("Transform")
    tr:sendMsg([[
        scale: 0.075,0.075,0.075;
        position: 0,]] .. playerSpawnHeight .. [[,0;
        rotation: 0,0,0;
    ]])
    player:addComponent("Rigidbody"):sendMsg([[
        shape: cube;
        type: dynamic;
        mass: 10.0;
        restitution: 0;
        colliderScale: 3,8,2;
    ]])
    local mesh = player:addComponent("Mesh")
    mesh:sendMsg([[meshName: Player.mesh]])
    local playerMov = player:addComponent("MovimientoJugador")
    playerMov:sendMsg([[
        speed: 30.0
    ]])

    player:addComponent("Animation"):sendMsg([[animName: idle]])

    local sliderBehindLive = player:addComponent("Slider")
    sliderBehindLive:sendMsg([[
        materialBar: Stamina2;
        materialBarBg: Heal_bg;
        materialButton: CircleButton;
        width: 500;
        height: 25;
        posX: 100;
        posY: 60;
        posZ: 0;
    ]])

   local sliderOverLive = player:addComponent("Slider")
   sliderOverLive:sendMsg([[
        materialBar: Heal;
        materialBarBg: Heal_bg;
        materialButton: CircleButton;
        width: 500;
        height: 25;
        posX: 100;
        posY: 60;
        posZ: 1;
    ]])

    local saludjugador = player:addComponent("Salud")
    saludjugador:sendComponent(0, sliderOverLive);
    saludjugador:sendComponent(1, sliderBehindLive);

    local sliderBehindSta = player:addComponent("Slider")
    sliderBehindSta:sendMsg([[
        materialBar: Stamina2;
        materialBarBg: Stamina_bg;
        materialButton: CircleButton;
        width: 300;
        height: 25;
        posX: 100;
        posY: 90;
        posZ: 0;
    ]])

   local sliderOverSta = player:addComponent("Slider")
   sliderOverSta:sendMsg([[
        materialBar: Stamina;
        materialBarBg: Stamina_bg;
        materialButton: CircleButton;
        width: 300;
        height: 25;
        posX: 100;
        posY: 90;
        posZ: 1;
    ]])

    local staminajugador = player:addComponent("Stamina")
    staminajugador:sendComponent(0, sliderOverSta);
    staminajugador:sendComponent(1, sliderBehindSta);


    local playerAttack = player:addComponent("AtaqueJugador")



    local dashParticles = scene:createObject("dashParticles")
    local trDash = dashParticles:addComponent("Transform")
    trDash:sendMsg([[scale: 1,1,1; position: 0,]] .. playerSpawnHeight - 1 .. [[,0; rotation: 0,0,0;]])
    local dashSys = dashParticles:addComponent("ParticleSystem")
    dashSys:sendMsg([[particleName: dash; emitting: false]])
    trDash:sendComponent(1, tr)

    -- Enemigo--


    local boss = scene:createObject("boss")
    local bossHealth = boss:addComponent("Salud")
    bossHealth:sendMsg([[
        maxHealth: 100
    ]])
    local bosstr = boss:addComponent("Transform")
    bosstr:sendMsg([[
        scale: 0.2,0.2,0.2;
        position: 30,24,-30;
        rotation: 0,0,0;
    ]])


    local sliderBehindLiveBoss = boss:addComponent("Slider")
    sliderBehindLiveBoss:sendMsg([[
        materialBar: Stamina2;
        materialBarBg: Heal_bg;
        materialButton: CircleButton;
        width: 1000;
        height: 25;
        posX: 135;
        posY: 650;
        posZ: 0;
    ]])

   local sliderOverLiveBoss = boss:addComponent("Slider")
   sliderOverLiveBoss:sendMsg([[
        materialBar: Heal;
        materialBarBg: Heal_bg;
        materialButton: CircleButton;
        width: 1000;
        height: 25;
        posX: 135;
        posY: 650;
        posZ: 1;
    ]])


    bossHealth:sendComponent(0, sliderOverLiveBoss);
    bossHealth:sendComponent(1, sliderBehindLiveBoss);
    playerAttack:sendComponent(1, bossHealth)

    local bossAI = boss:addComponent("BossMelee")
    bossAI:sendComponent(0, tr)
    boss:addComponent("Mesh"):sendMsg([[meshName: Boss.mesh]])
    local bossRb = boss:addComponent('Rigidbody')
    bossRb:sendMsg([[
        state: dynamic;
        mass: 100.0;
        shape: sphere;
        restitution: 0.0;
        colliderScale: 18,18,18;
    ]])

    playerMov:sendComponent(0, bossRb)
    playerMov:sendComponent(1, trcam)
    playerAttack:sendComponent(0,bosstr)

    boss:addComponent("Animation"):sendMsg([[animName: idle]])

    -- haciendo hijo del hijo del player a la  "cam"
    trcam:sendComponent(1, compTrBolaHijaJug)

    -- Metiendo componente rotar Camara
    rotarcam:sendMsg([[
        verSens: 5.5
        horiSens: 5.5
    ]])

    camFollow:sendComponent(0, tr)

    rotarcam:sendGameObject(0, boss)
    rotarcam:sendGameObject(1, player)
    rotarcam:sendGameObject(2, cam)

    sceneboss1:createSmoke("Smoke1", 0, 0, -180)
    sceneboss1:createSmoke("Smoke2", 50, 0, -170)
    sceneboss1:createSmoke("Smoke3", -100, 0, -160)
    sceneboss1:createSmoke("Smoke4", -170, 0, 0)
    sceneboss1:createSmoke("Smoke5", -190, 0, 80)
    sceneboss1:createSmoke("Smoke1", 170, 0, 0)

    sceneboss1:createMesh("columna.mesh", -150, 10, 150, 10, 40, 10, 0,0,0)
    sceneboss1:createMesh("columna2.mesh", 150, 10, -150, 10, 40, 10, 0,0,0)
    sceneboss1:createMesh("columna3.mesh", -150, 10, -150, 10, 40, 10, 0,0,0)
    sceneboss1:createMesh("columna3.mesh", 150, 10, 150, 10, 40, 10, 0,0,0)
    sceneboss1:createMesh("wallRock1.mesh", 110, -5, 150, 5, 2, 3, 0,-0.7,0)
    sceneboss1:createMesh("wallRock1.mesh", 150, -5, 110, 5, 2, 3, 0,0.85,0)
    sceneboss1:createMesh("wallRock2.mesh", 150, -5, -110, 5, 2, 3, 0,1.6,0)
    sceneboss1:createMesh("wallRock1.mesh", -110, -5, -150, 5, 2, 3, 0,-0.7,0)
    sceneboss1:createMesh("wallRock2.mesh", -150, -5, 110, 5, 2, 3, 0,-1.6,0)
    sceneboss1:createMesh("wallRock1.mesh", -150, -5, 0, 5, 2, 3, 0,0.85,0)

    local lluviaParticle = scene:createObject("Lluvia")
    lluviaParticle:addComponent("Transform"):sendMsg([[scale: 1,1,1; position: 0,100,0; rotation: 0,0,0;]])
    local lluviaParticleSys = lluviaParticle:addComponent("ParticleSystem")
    lluviaParticleSys:sendMsg([[particleName: lluvia; emitting: true]])

    local torch = scene:createObject("Lluvia")
    torch:addComponent("Transform"):sendMsg([[scale: 1,1,1; position: -30,10,0; rotation: 0,0,0;]])
    local torchSys = torch:addComponent("ParticleSystem")
    torchSys:sendMsg([[particleName: torch; emitting: true]])

    local skybox = scene:createObject("Skybox")
    skybox:addComponent("Skybox"):sendMsg([[materialName: skyboxhell; distance: 300; ]])

    createVignette()
    scene:createObject("Pause Game"):addComponent("PauseGame")

    local bulletGenerator = scene:createObject("BulletGen")
    bulletGenerator:addComponent("Transform"):sendMsg([[
    scale: 1,1,1;
    position: 0,10,-125;
    rotation: 0,0,0;]])
    bulletGenerator:addComponent("BulletGenerator"):sendMsg([[
    interval: 5;
    area: -140,20,140;
    ]])

    local soundObjBoss = scene:createObject("menuSound")
    local soundCompBoss= soundObjBoss:addComponent("Sound")
    soundCompBoss:sendMsg([[soundName: SongFire.wav; channel: music; loop: true; volume: 0.5; playNow: true;]])

    -- local dialogue = scene:createObject("Dialogue"):addComponent('Dialogue')
    -- dialogue:sendMsg("lines: 3")

    -- for i = 0, 2, 1 do
    --     local line = createText(20, 500 + i * 30, '  ')
    --     dialogue:sendComponent(i, line);
    -- end
    -- dialogue:sendMssg([[
    --     line0: #Soy el primer texto uwu#
    --     line1: #Soy el segundo texto uwu#
    --     line2: #Soy el tercer texto uwu...#
    -- ]])
    -- dialogue:sendMssg([[
    --     line0: #Soy el cuarto texto uwu#
    --     line1: #Soy el quinto texto uwu#
    --     line2: #Soy el sexto texto uwu...#
    -- ]])
    -- dialogue:sendMssg([[
    --     line0: #Hola nene, mi nombre es Yojhan Steven, si estas#
    --     line1: #viendo esto es porque eres una persona muy#
    --     line2: #atenta Muchas gracias por tu tiempo.#
    -- ]])
end

return sceneboss1