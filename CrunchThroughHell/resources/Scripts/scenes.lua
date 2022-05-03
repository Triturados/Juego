-- Escenas del juego: 
--  0: menu
--  1: settings
--  2: pause
--  3: overworld
--  4: boss1
--  5: boss2
--  6: victory
--  7: defeat
--------------



package.path = package.path .. ";./resources/Scripts/?.lua"
--package.path = package.path .. ";/resources/Scripts/?.lua"

sceneCount = 8;

scene2 = {
    name = "Pause",
    objects = {
        {
            name = "Camera",
            components = {
                {
                    type = 'Transform',
                    info = [[
                        scale: 2,2,2;
                        position: 0,40,80;
                        rotation: 0,0,0;
                    ]]
                },
                {
                    type = 'Camera',
                    info = [[
                        name: pause;
                        zOrder: 2
                    ]]
                }
            }
        },
        {
            name = "Background",
            components = {
                    {
                        type = 'Image',
                        info = [[
                            material: pauseMenu; 
                            width: 1280;
                            height : 720;
                        ]]
                    }
                }
        },
        {
            name = "Vignette",
            components = {
                    {
                        type = 'Image',
                        info = [[
                            material: splashScreen_vignette; 
                            width: 1280;
                            height : 720;
                        ]]
                    }
                }
        },
    },
    code = function()
        local continue = scene:createObject("Start Button"):addComponent("Button");
        local exitButton = scene:createObject("Exit Button"):addComponent("Button");
    
        continue:sendMsg([[
            material: Heal_bg;
            width: 100;
            height: 50;
            posX: 500;
            posY: 300;
            posZ: 1
        ]])
    
        exitButton:sendMsg([[
            material: Heal_bg;
            width: 100;
            height: 50;
            posX: 500;
            posY: 360;
            posZ: 1
        ]])

        local menuObj = scene:createObject("Pause Component"):addComponent("PauseMenu")
        menuObj:sendComponent(0, continue);
        menuObj:sendComponent(1, exitButton);
    end
}
function scene0() -- Main menu
    scene:name("Main menu")
    --menu = require "menu";
    --menu:cambiarIcono()
    --icon('icon.bmp')

    local cam = scene:createObject("cam")
    cam:addComponent('Transform'):sendMsg([[
        scale: 2,2,2;
        position: 0,40,80;
        rotation: 0,0,0;
    ]])

    cam:addComponent('Camera'):sendMsg([[
        name: escenaMenu;
        zOrder: -1
    ]])
    
    local zOrder = 0
    local bg = scene:createObject("Background");
    bg:addComponent("Image"):sendMsg([[
        material: mainmenuBackgroundImage; 
        width: 1280;
        height : 720;
        posZ: ]] .. zOrder ..[[
    ]])
    zOrder = zOrder + 1

    local bannerxpos = 100;
    local bannerwidth = 300;
    local centerx = round((100 + 300) * 0.5)

    local containerObj = scene:createObject("Container")
    containerObj:addComponent('MoveUI'):sendMssg([[
        destination: 100, 0, 0;
        duration: 3.0;
        enabled: true;
    ]])

    local container = containerObj:addComponent("UIContainer")
    container:sendMssg([[
        posX: 100;
        posY: -720;
        posZ: 0;
    ]])

    container:sendComponent(0, scene:createObject("Banner"):addComponent("Image"):sendMsg([[
        material: mainmenuBanner; 
        width: 300;
        height : 640;
        posX: 0;
        posY: 52
        posZ: ]] .. zOrder ..[[
    ]]))
    zOrder = zOrder + 1

    
    scene:createObject("Press any key"):addComponent("Image"):sendMsg([[
        material: mainmenuPressKey; 
        width: 381;
        height : 29;
        posZ: ]] .. zOrder ..[[
    ]])
    zOrder = zOrder + 1



    local mainmenu = bg:addComponent("MainMenu");
    local initialHeigh = 380
    for i = 0, 5, 1 do
        local button = scene:createObject("Menu button " .. i):addComponent('Button');

        local w = 200
        local x = (width() - w) / 2;
        button:sendMsg([[
            material: mainmenuButton ]]..i..[[;
            width: ]] .. w .. [[;
            height: 50;
            posX: ]] .. round(x) .. [[;
            posY: ]] .. (initialHeigh + 60 * i) .. [[ ;
            posZ: 2
        ]])

        mainmenu:sendComponent(i, button)
    end

    mainmenu:sendComponent(-1, createArrow(height() - 60, 'mainmenuArrowDown'))
    mainmenu:sendComponent(-2, createArrow(426, 'mainmenuArrow'))
    mainmenu:sendMssg('centerX: 250');



    scene:createObject("Black border"):addComponent("Image"):sendMsg([[
        material: mainmenuBlackBorder; 
        width: 1280;
        height : 720;
        posZ: ]] .. zOrder ..[[
    ]])
    zOrder = zOrder + 1

    Blueprint.spawnObject(scene, "Vignette")

end

function createArrow(pos, mat)
    local button = scene:createObject("Displacement button"):addComponent('Button');

    local w = 50
    local x = round((width() - w) / 2);

    x = 10

    button:sendMsg([[
        material: ]] .. mat .. [[;
        width: ]] .. w .. [[;
        height: ]] .. w .. [[;
        posX: ]] .. x .. [[;
        posY: ]] .. pos .. [[ ;
        posZ: 6
    ]])

    -- print(mapa['objects']['name'])
    return button
end

function createCharco(name, type, x,y,z)
    local charco = scene:createObject(name);

    local tr = charco:addComponent("Transform");

    tr:sendMsg([[
        scale: 10,1,10;
        position: ]] .. x .. [[ , ]] .. y .. [[ , ]] .. z .. [[;
        rotation: 0,0,0;
    ]])

    charco:addComponent("Mesh"):sendMsg([[
        meshName: Charco.mesh;
    ]])

    charco:addComponent('Rigidbody'):sendMsg([[
        trigger: true;
        mass: 0.0;
        shape: cube; 
        restitution: 0.9;
        colliderScale: 10,1,10;
    ]])

    charco:addComponent('EfectoEscenario'):sendMsg([[
        type: ]] .. type .. [[
    ]])
    
    return tr;

end

function scene1() -- Settings
    scene:name("Settings")

    local cam = scene:createObject("cam")
    local trcam = cam:addComponent('Transform')
    trcam:sendMsg([[
        scale: 2,2,2;
        position: 0,40,80;
        rotation: 0,0,0;
    ]])

    local camCamera = cam:addComponent('Camera')

    camCamera:sendMsg([[
        name: settings;
        zOrder: -1
    ]])

    local bg = scene:createObject("Background");
    bg:addComponent("Transform")
    bg:addComponent("Image"):sendMsg([[
        material: backgroundMenu; 
        width: 1280;
        height : 720;
    ]])

    local startButton = scene:createObject("Start Button"):addComponent("Button");
    local exitButton = scene:createObject("Exit Button"):addComponent("Button");

    startButton:sendMsg([[
        material: Heal_bg;
        width: 100;
        height: 50;
        posX: 500;
        posY: 300;
		posZ: 1
    ]])

    exitButton:sendMsg([[
        material: Heal_bg;
        width: 100;
        height: 50;
        posX: 500;
        posY: 360;
		posZ: 1
    ]])

    local mainmenu = bg:addComponent("MainMenu");
    mainmenu:sendComponent(0, startButton);
    mainmenu:sendComponent(1, exitButton);
end

function scene3() -- Overworld
    scene:name("Escena de Prueba")

    persistentObject:addComponent("ComponenteDeContar")

    local a = scene:createObject("AAA");
    a:addComponent("MoverPantalla"):sendMsg("inicial: 0.1")

    -- local btest = scene:createObject("btest");
    -- btest:addComponent("Button"):sendMsg([[
    --     material: Heal_bg;
    --     width: 300;
    --     height: 50;
    --     posX: 400;
    --     posY: 100;
    -- ]])

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
    local charcoTr = createCharco("Charco1", 1, 0,2,70)
    local charcoTr2 = createCharco("Charco2", 1, -70,2, -70)
    local charcoTr3 =  createCharco("Charco3", 1, 70,2,-70)

    -- Colocamos el padre
    sueloTr:sendMsg([[
        scale: 4,1,4;
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
    -- Volvemos a mover el escenario (si hiciese falta)
    -- sueloTr:sendMsg([[
    --     position: 0,0,0;
    --     rotation: 0,0,0,0;
    -- ]])

    local comp3 = suelo:addComponent("Mesh")
    comp3:sendMsg([[
        meshName: arena.mesh;
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
    material:sendMsg([[materialName: bolaroja]])
    material:sendComponent(0, comp3)

    -- Camara comentada por lo del splash screen
    -- local camara = scene:createObject("CamaritaGuapa")
    -- local transcam = camara:addComponent('Transform')
    -- transcam:sendMsg([[
    --    scale: 1,1,1;
    --    position: 0,40,80;
    --    rotation: 0,0,0,0;
    -- ]])

    -- local camCamera = camara:addComponent('Camera')

    -- camCamera:sendMsg([[
    --    name: escenaJuego;
    -- ]])
   

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
        position: 0,40,60;
        rotation: 0,0,0;
    ]])

    local camCamera = cam:addComponent('Camera')
    local camFollow = cam:addComponent('CamFollow')

    camCamera:sendMsg([[
        name: escenaJuego;
        zOrder: -3;
    ]])
    camCamera:sendMsg([[
        compositor: Posterize;
    ]])

    -- player--
    local player = scene:createObject("jugador")
    local tr = player:addComponent("Transform")
    tr:sendMsg([[
        scale: 0.075,0.075,0.075;
        position: 0,30,0;
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

    --player:addComponent("ParticleSystem")

    player:addComponent("Animation"):sendMsg([[animName: idle]])

    local sliderBehindLive = player:addComponent("Slider"):sendMsg([[
        materialBar: Heal;
        materialBarBg: Heal_bg;
        materialButton: CircleButton;
        width: 500;
        height: 25;
        posX: 100;
        posY: 60;
    ]])

   local sliderOverLive = player:addComponent("Slider"):sendMsg([[
        materialBar: Heal;
        materialBarBg: Heal_bg;
        materialButton: CircleButton;
        width: 500;
        height: 25;
        posX: 100;
        posY: 60;
    ]])

    local saludjugador = player:addComponent("SaludJugador")
    saludjugador:sendComponent(0, sliderOverLive);
    saludjugador:sendComponent(1, sliderBehindLive);

    local sliderBehindSta = player:addComponent("Slider"):sendMsg([[
        materialBar: Stamina;
        materialBarBg: Stamina_bg;
        materialButton: CircleButton;
        width: 300;
        height: 25;
        posX: 100;
        posY: 90;
    ]])

   local sliderOverSta = player:addComponent("Slider"):sendMsg([[
        materialBar: Stamina;
        materialBarBg: Stamina_bg;
        materialButton: CircleButton;
        width: 300;
        height: 25;
        posX: 100;
        posY: 90;
    ]])

    local staminajugador = player:addComponent("Stamina")
    staminajugador:sendComponent(0, sliderOverSta);
    staminajugador:sendComponent(1, sliderBehindSta);


    local playerAttack = player:addComponent("AtaqueJugador")

    local dashParticles = scene:createObject("dashParticles")
    local trDash = dashParticles:addComponent("Transform")
    trDash:sendMsg([[scale: 1,1,1; position: 0,35,0; rotation: 0,0,0;]])
    local dashSys = dashParticles:addComponent("ParticleSystem")
    dashSys:sendMsg([[particleName: dash; emitting: false]])
    trDash:sendComponent(1, tr)

    -- Enemigo--
    
    local soundObjBoss = scene:createObject("menuSound")
    local soundCompBoss= soundObjBoss:addComponent("Sound")
    soundCompBoss:sendMsg([[soundName: FireNight.wav; channel: music; loop: true; volume: 0.5; playNow: true;]])

    local boss = scene:createObject("boss")
    local bosstr = boss:addComponent("Transform")
    bosstr:sendMsg([[
        scale: 0.2,0.2,0.2;
        position: 50,20,-50;
        rotation: 0,0,0;
    ]])
    local bossAI = boss:addComponent("BossMelee")
    bossAI:sendComponent(0, tr)
    boss:addComponent("Mesh"):sendMsg([[meshName: Boss.mesh]])
    local bossRb = boss:addComponent('Rigidbody')
    bossRb:sendMsg([[
        state: dynamic;
        mass: 10.0;
        shape: sphere; 
        restitution: 1.0;
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

    --local particleSys = scene:createObject("Bomba")
    --particleSys:addComponent("Transform"):sendMsg([[scale: 1,1,1; position: 0,5,-20; rotation: 0,0,0;]])
    --local pSys = particleSys:addComponent("ParticleSystem")
    --pSys:sendMsg([[particleName: bomb; emitting: true]])

    local lluviaParticle = scene:createObject("Lluvia")
    lluviaParticle:addComponent("Transform"):sendMsg([[scale: 1,1,1; position: 0,100,0; rotation: 0,0,0;]])
    local lluviaParticleSys = lluviaParticle:addComponent("ParticleSystem")
    lluviaParticleSys:sendMsg([[particleName: lluvia; emitting: true]])

    local torch = scene:createObject("Lluvia")
    torch:addComponent("Transform"):sendMsg([[scale: 1,1,1; position: -30,10,0; rotation: 0,0,0;]])
    local torchSys = torch:addComponent("ParticleSystem")
    torchSys:sendMsg([[particleName: torch; emitting: true]])

    local textPrueba = scene:createObject("TextoPrueba")
    local textPruebaText = textPrueba:addComponent("Text")
    textPruebaText:sendMsg([[
        position: 50, 50, 0;
        fontName: chikory
        mainColor: 0.3, 1.0, 0.6, 1.0;
        textScale: 0.05
        alignment : 0
        ]])

    -- textPruebaText:sendString("V I D A S")
    local showText = textPrueba:addComponent("ShowText")
    showText:sendMssg([[
        interval: 0.1
    ]])
    showText:sendString("Hola que tal como estas")
    createText(20, 100, 'tititiitiutututu')
    local dialogue = scene:createObject("Dialogue"):addComponent('Dialogue')
    dialogue:sendMsg("lines: 3")

    for i = 0, 2, 1 do
        local line = createText(20, 500 + i * 30, '  ')
        dialogue:sendComponent(i, line);
    end
    dialogue:sendMssg([[
        line0: #Soy el primer texto uwu#
        line1: #Soy el segundo texto uwu#
        line2: #Soy el tercer texto uwu...#
    ]])
    dialogue:sendMssg([[
        line0: #Soy el cuarto texto uwu#
        line1: #Soy el quinto texto uwu#
        line2: #Soy el sexto texto uwu...#
    ]])
    dialogue:sendMssg([[
        line0: #Hola nene, mi nombre es Yojhan Steven, si estas#
        line1: #viendo esto es porque eres una persona muy#
        line2: #atenta Muchas gracias por tu tiempo.#
    ]])
    -- textPrueba2text:sendString("Soy el segundo texto uwu")

    local skybox = scene:createObject("Skybox")
    skybox:addComponent("Skybox"):sendMsg([[materialName: skyboxhell; distance: 300; ]])

    createVignette()
    scene:createObject("Pause Game"):addComponent("PauseGame")

    local bulletGenerator = scene:createObject("BulletGen")
    bulletGenerator:addComponent("Transform"):sendMsg([[        
    scale: 1,1,1;
    position: 0,10,-150;
    rotation: 0,0,0;]])
    bulletGenerator:addComponent("BulletGenerator"):sendMsg([[
    interval: 5;
    area: -100,20,100;
    ]])
end

function scene4() -- Boss1
end

function scene5() -- Boss2
end

function scene6() -- Victory
    scene:name("Escena victoria")

    local cam = scene:createObject("cam")
    local trcam = cam:addComponent('Transform')
    trcam:sendMsg([[
        scale: 2,2,2;
        position: 0,40,80;
        rotation: 0,0,0;
    ]])

    local camCamera = cam:addComponent('Camera')

    camCamera:sendMsg([[
        name: escenaMuerte;
        zOrder: -2
    ]])

    local bg = scene:createObject("Background");
    bg:addComponent("Transform")
    bg:addComponent("Image"):sendMsg([[
        material: menuDeadBackground; 
        width: 1280;
        height : 720;
    ]])

    local victorymenu = bg:addComponent("DeadMenu");
    createVignette()
end

function scene7() -- Defeat
    scene:name("Escena derrota")

    local cam = scene:createObject("cam")
    local trcam = cam:addComponent('Transform')
    trcam:sendMsg([[
        scale: 2,2,2;
        position: 0,40,80;
        rotation: 0,0,0;
    ]])

    local camCamera = cam:addComponent('Camera')

    camCamera:sendMsg([[
        name: escenaMuerte;
        zOrder: -2
    ]])

    local bg = scene:createObject("Background");
    bg:addComponent("Transform")
    bg:addComponent("Image"):sendMsg([[
        material: menuDeadBackground; 
        width: 1280;
        height : 720;
    ]])

    local deadmenu = bg:addComponent("DeadMenu");
    createVignette()
end

function createText(x, y, text)
    local textObj = scene:createObject("textObj")
    local textComp = textObj:addComponent("Text")
    textComp:sendMsg([[
        position: ]] .. x .. ',' .. y .. [[, 0;
        fontName: SourceSansProLight
        mainColor: 1, 1, 1, 1.0;
        textScale:0.05
        alignment : 0
        ]])
    local showText = textObj:addComponent("ShowText")
    showText:sendMssg([[
        interval: 0.1
        ]])
    showText:sendString(text)
    return showText
end

function createVignette()
    scene:createObject('Vignette'):addComponent('Image'):sendMssg([[
        material: splashScreen_vignette; width: 1280; height : 720; posZ: 20
    ]])
end

----------Objetos escena------------

