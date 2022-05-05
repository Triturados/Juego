-- Escenas del juego:
--  0: menu
--  1: settings
--  2: pause
--  3: overworld
--  4: boss1
--  5: boss2
--  6: victory
--  7: defeat
--  8: credits
--  9: About
-- 10: How to play
--------------
sceneCount = 11;

package.path = package.path .. ";./resources/Scripts/?.lua"
package.path = package.path .. ";../../resources/Scripts/?.lua"

menu = require "menu";
sceneboss1 = require "sceneboss1";
sceneboss2 = require "sceneboss2";

icon('iconkatana.bmp')

function scene0() -- Main menu
    menu:createMainMenu()
end

function scene1() -- Settings
    menu:createSettings()
end

scene2 = menu:menuPausa(); -- Pause Menu

function scene8() -- Credits
    menu:createCredits()
end

function scene9() -- About
    menu:createAbout()
end

function scene10() -- How to play
    menu:createHowtoplay()
end

function scene3() -- Overworld de verdad

    scene:name("Escena Overworld")

    -- Limites mundo --
    -- MURO1
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

    -- MURO2
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

    -- MURO3
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

    -- MURO4
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

    -- Creacion del sonido del boss2
    local soundOverWorld = scene:createObject("overSound")
    local soundOverWorldComp = soundOverWorld:addComponent("Sound")
    soundOverWorldComp:sendMsg(
        [[soundName: HandPanOverWorld.wav; channel: music; loop: true; volume: 0.5; playNow: true;]])

    -- Suelo--
    local suelo = scene:createObject("Suelo")
    local sueloTr = suelo:addComponent("Transform")
    -- Colocamos el padre
    sueloTr:sendMsg([[
        scale: 150,1,150;
        position: 0,-4,0;
        rotation: 0,0,0;
    ]])
    local sueloMesh = suelo:addComponent("Mesh")
    sueloMesh:sendMsg([[
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
    material:sendMsg([[materialName: GrisSinBrillo]])
    material:sendComponent(0, sueloMesh)

    --------------------------------------------
    -- hijosmuros --
    muroTr1:sendComponent(1, sueloTr)
    muroTr2:sendComponent(1, sueloTr)
    muroTr3:sendComponent(1, sueloTr)
    muroTr4:sendComponent(1, sueloTr)
    ------------------------------

    local luz = scene:createObject("Luz")
    local luzTr = luz:addComponent('Transform')
    luzTr:sendMsg([[
        scale: 1,1,1;
        position: 0,40,0;
        rotation: -45,0,0;
    ]])
    local compLight = luz:addComponent('Light')
    compLight:sendMssg([[
        name: luz_direccional
        type: directional
    ]])

    -- CAMARA
    local cam = scene:createObject("cam")
    local trcam = cam:addComponent('Transform')

    trcam:sendMsg([[
        scale: 2,2,2;
        position: 0,45,200;
        rotation: -0.25,0,0;
    ]])

    local camCamera = cam:addComponent('Camera')

    camCamera:sendMsg([[
        name: escenaOverWorld;
        zOrder: 1;
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
        speed: 30.0;
        overWorld: true;

    ]])

    local sliderBehindSta = player:addComponent("Slider")
    sliderBehindSta:sendMsg([[
        materialBar: Stamina2;
        materialBarBg: Stamina_bg;
        materialButton: CircleButton;
        width: 300;
        height: 25;
        posX: 100;
        posY: -20;
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
        posY: -20;
        posZ: 1;
    ]])

    local staminajugador = player:addComponent("Stamina")
    staminajugador:sendComponent(0, sliderOverSta);
    staminajugador:sendComponent(1, sliderBehindSta);


    local dashParticles = scene:createObject("dashParticles")
    local trDash = dashParticles:addComponent("Transform")
    trDash:sendMsg([[scale: 1,1,1; position: 0,15,0; rotation: 0,0,0;]])
    local dashSys = dashParticles:addComponent("ParticleSystem")
    dashSys:sendMsg([[particleName: dash; emitting: false]])
    trDash:sendComponent(1, tr)

    player:addComponent("Animation"):sendMsg([[animName: idle]])

    --local playerAttack = player:addComponent("AtaqueJugador")

    playerMov:sendComponent(1, trcam)

    sceneboss1:createMesh("columna.mesh", -150, 10, 150, 10, 40, 10, 0, 0, 0)
    sceneboss1:createMesh("columna2.mesh", 150, 10, -150, 10, 40, 10, 0, 0, 0)
    sceneboss1:createMesh("columna3.mesh", -150, 10, -150, 10, 40, 10, 0, 0, 0)
    sceneboss1:createMesh("columna3.mesh", 150, 10, 150, 10, 40, 10, 0, 0, 0)
    sceneboss1:createMesh("wallRock1.mesh", 110, -5, 150, 5, 2, 3, 0, -0.7, 0)
    sceneboss1:createMesh("wallRock1.mesh", 150, -5, 110, 5, 2, 3, 0, 0.85, 0)
    sceneboss1:createMesh("wallRock2.mesh", 150, -5, -110, 5, 2, 3, 0, 1.6, 0)
    sceneboss1:createMesh("wallRock1.mesh", -110, -5, -150, 5, 2, 3, 0, -0.7, 0)
    sceneboss1:createMesh("wallRock2.mesh", -150, -5, 110, 5, 2, 3, 0, -1.6, 0)
    sceneboss1:createMesh("wallRock1.mesh", -150, -5, 0, 5, 2, 3, 0, 0.85, 0)

    local skybox = scene:createObject("Skybox")
    skybox:addComponent("Skybox"):sendMsg([[materialName: skyboxhell; distance: 300; ]])

    createVignette()
    scene:createObject("Pause Game"):addComponent("PauseGame")

    local textoInteractuar = scene:createObject("texto")
    textoInteractuar:addComponent("Text"):sendMsg([[
    posX: ]] .. round(width() / 2) .. [[;
    posY: ]] .. round(height() * 0.85) .. [[;
    alignment: 2;
    fontName: SourceSansProLight
    textScale: 0.05;
    mainColor: 1,1,1,1;]])
    local showText = textoInteractuar:addComponent("ShowText"):sendMsg([[
        interval: 0.025;
    ]])

    -- boss1

    local boss1 = scene:createObject("boss1")
    local boss1tr = boss1:addComponent("Transform")
    boss1tr:sendMsg([[
        scale: 0.3,0.3,0.3;
        position: -70,30,-50;
        rotation: 0,0.4,0;
    ]])
    local bossMesh = boss1:addComponent("Mesh")
    bossMesh:sendMsg([[meshName: Boss.mesh]])

    local boss1Rb = boss1:addComponent('Rigidbody')
    boss1Rb:sendMsg([[
    state: static;
    mass: 50000.0;
    shape: cube;
    restitution: 0.0;
    colliderScale: 18,60,18;
    ]])

    local boss1Anim = boss1:addComponent("Animation"):sendMsg([[
        animName: idle;
        initialState: true;
        initialLoop: true;
        ]])

    local boss1Interact = boss1:addComponent("BossDialog")
        boss1Interact:sendComponent(0,tr)
        boss1Interact:sendComponent(1,showText)
        boss1Interact:sendMsg([[
            bossNum: 1;
        ]])
        --boss2

    local boss2 = scene:createObject("boss2")
    local boss2tr = boss2:addComponent("Transform")
    boss2tr:sendMsg([[
        scale: 0.045,0.045,0.045;
        position: 70,30,-50;
        rotation: 0,-0.4,0;
    ]])
    local boss2Mesh = boss2:addComponent("Mesh")
    boss2Mesh:sendMsg([[meshName: Boss2.mesh]])

    local boss2Rb = boss2:addComponent('Rigidbody')
    boss2Rb:sendMsg([[
    state: static;
    mass: 50000.0;
    shape: cube;
    restitution: 0.0;
    colliderScale: 18,60,18;
    ]])

    local boss2Anim = boss2:addComponent("Animation"):sendMsg([[
    animName: idle;
    initialState: true;
    initialLoop: true;
    ]])


    local boss2Interact = boss2:addComponent("BossDialog")
    boss2Interact:sendComponent(0,tr)
    boss2Interact:sendComponent(1,showText)
    boss2Interact:sendMsg([[
            bossNum: 2;
            boss1Defeated:false;
        ]])


    local boss1Dialogue = scene:createObject("DialogueBoss1"):addComponent('Dialogue')
    boss1Dialogue:sendMsg("lines: 3")

    for i = 0, 2, 1 do
        local line = createText(round(width()/2), round(height() * 0.8 + i * 30), '  ')
        boss1Dialogue:sendComponent(i, line);
    end
    boss1Dialogue:sendMssg([[
        line0: #Welcome to the overworld you little worm.#
        line1: #You will have to defeat me: YOJHANSAN and my master DANIEL#
        line2: #If you wanna get out of here. Good luck#
    ]])

    boss1Interact:sendComponent(2,boss1Dialogue)


    local boss1DialogueAlternate = scene:createObject("DialogueBoss1Alternate"):addComponent('Dialogue')
    boss1DialogueAlternate:sendMsg("lines: 3")

    for i = 0, 2, 1 do
        local line = createText(round(width()/2), round(height() * 0.8 + i * 30), '  ')
        boss1DialogueAlternate:sendComponent(i, line);
    end
    boss1DialogueAlternate:sendMssg([[
        line0: #I underestimated you worm#
        line1: #Anyway DANIEL is gona split you into pieces#
        line2: #If I were you i wouldnt even try#
    ]])

    boss1Interact:sendComponent(3,boss1DialogueAlternate)

    local boss2Dialogue = scene:createObject("DialogueBoss2"):addComponent('Dialogue')
    boss2Dialogue:sendMsg("lines: 3")

    for i = 0, 2, 1 do
        local line = createText(round(width()/2), round(height() * 0.8 + i * 30), '  ')
        boss2Dialogue:sendComponent(i, line);
    end
    boss2Dialogue:sendMssg([[
        line0: #You have defeated YOJHASAN but he is just a mere apprentice.#
        line1: #You better run away if you dont want to get destroyed...#
        line2: #Try if u dont believe me, my power is unmesurable#
    ]])

    boss2Interact:sendComponent(4,boss2Dialogue)

    
    local boss2DialogueAlternate = scene:createObject("DialogueBoss2Alternate"):addComponent('Dialogue')
    boss2DialogueAlternate:sendMsg("lines: 3")

    for i = 0, 2, 1 do
        local line = createText(round(width()/2), round(height() * 0.8 + i * 30), '  ')
        boss2DialogueAlternate:sendComponent(i, line);
    end
    boss2DialogueAlternate:sendMssg([[
        line0: #HAHAHAHAHAHAHAHAHHAAHHAHAA#
        line1: #You couldnt defeat YOJHASAN and u wanna try against me?#
        line2: #Dont be an idiot and defeat YOJHASAN if u wanna fight me#
    ]])

    boss2Interact:sendComponent(5,boss2DialogueAlternate)

    -- TIENDA

    local shop = scene:createObject('Shop'):addComponent('Shop'):sendMssg([[
        speedIncrement: 30;
    ]]);

    for i = 0, 2, 1 do

        local buttonwidth = 200;
        local margin = 100;
        local xpos = round((width() - buttonwidth) * 0.5 - buttonwidth - margin + (buttonwidth + margin) * i);
        shop:sendComponent(i, menu:createButton('mainmenuButton', xpos, 500, 11, buttonwidth, 50));
    end

    print('Overworldo')
end

function scene4() -- Boss1
    sceneboss1:createScene()
end

function scene5() -- Boss2
    sceneboss2:createScene2()
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
        material: menuWinBackground;
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
        posX: ]] .. x .. [[;
        posY: ]] .. y .. [[;
        posZ: ]] .. 0 .. [[;
        fontName: SourceSansProLight
        mainColor: 1, 1, 1, 1.0;
        textScale:0.05
        alignment : 2
        ]])
    local showText = textObj:addComponent("ShowText")
    showText:sendMssg([[
        interval: 0.025
        ]])
    showText:sendString(text)
    return showText
end

function createVignette()
    scene:createObject('Vignette'):addComponent('Image'):sendMssg([[
        material: splashScreen_vignette; width: 1280; height : 720; posZ: 20
    ]])
end

function createArbol(name, x, y, z)
    local arbol = scene:createObject(name);

    local tr = arbol:addComponent("Transform");

    tr:sendMsg([[
        scale: 20,20,20;
        position: ]] .. x .. [[ , ]] .. y .. [[ , ]] .. z .. [[;
        rotation: 0,0,0;
    ]])

    arbol:addComponent("Mesh"):sendMsg([[
        meshName: Arbol1.mesh;
    ]])

    arbol:addComponent('Rigidbody'):sendMsg([[
        mass: 0.0;
        state: static;
        shape: cube;
        restitution: 0.9;
        colliderScale: 15,25,15;
    ]])

    return tr;

end

----------Objetos escena------------

