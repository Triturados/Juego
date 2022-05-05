
local sceneboss2 = {}

package.path = package.path .. ";./resources/Scripts/?.lua"
package.path = package.path .. ";../../resources/Scripts/?.lua"

sceneboss1 = require "sceneboss1";

function sceneboss2:createScene2() 

-- Creamos Camara
local cam = scene:createObject("cam")
local trcam = cam:addComponent('Transform')

trcam:sendMsg([[
    scale: 2,2,2;
    position: 0,40,60;
    rotation: 0,0,0;
]])

local camCamera = cam:addComponent('Camera')

-- Luz General
local luz = scene:createObject("Luz")
local compLuz = luz:addComponent('Transform')

compLuz:sendMsg([[
    scale: 1,1,1;
    position: 0,20,0;
    rotation: -90,0,0;
]])

local compLight = luz:addComponent('Light')
compLight:sendMssg([[
    name: luz_direccional
    type: directional
    power: 1.1
]])

camCamera:sendMsg([[
    compositor: Posterize;
]])

-- Creacion del sonido del boss2
local soundObjBoss = scene:createObject("menuSound")
local soundCompBoss = soundObjBoss:addComponent("Sound")
soundCompBoss:sendMsg([[soundName: SongFire.wav; channel: music; loop: true; volume: 0.5; playNow: true;]])

-- Creamos Suelo
local suelo = scene:createObject("Suelo")
local sueloTr = suelo:addComponent("Transform")

sueloTr:sendMsg([[
    scale: 350,1,350;
    position: 0,-4,0;
    rotation: 0,0,0;
]])

local comp3 = suelo:addComponent("Mesh")
comp3:sendMsg([[
    meshName: cube.mesh;
]])
local compRigidbodySuelo = suelo:addComponent('Rigidbody')
compRigidbodySuelo:sendMsg([[
    trigger: false;
    state: static;
    mass: 0.0;
    shape: cube;
    restitution: 0.9;
    colliderScale: 350,1,350;
    ]])

local material = suelo:addComponent("Material")
material:sendMsg([[materialName: Astral_scenario]])
material:sendComponent(0, comp3)

-- skyBox
local skybox = scene:createObject("Skybox")
skybox:addComponent("Skybox"):sendMsg([[materialName: skyboxblue; distance: 300; ]])

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

player:addComponent("Animation"):sendMsg([[animName: idle]])

local sliderBehindLive = player:addComponent("Slider")
sliderBehindLive:sendMsg([[
    materialBar: Heal;
    materialBarBg: Heal_bg;
    materialButton: CircleButton;
    width: 500;
    height: 25;
    posX: 100;
    posY: 60;
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
]])

local saludjugador = player:addComponent("Salud")
saludjugador:sendComponent(0, sliderOverLive);
saludjugador:sendComponent(1, sliderBehindLive);

local sliderBehindSta = player:addComponent("Slider")
sliderBehindSta:sendMsg([[
    materialBar: Stamina;
    materialBarBg: Stamina_bg;
    materialButton: CircleButton;
    width: 300;
    height: 25;
    posX: 100;
    posY: 90;
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
-----------------------------------PELIGRO----------------------------------------------------
-- AHORA SE VIENE LA MOVIDA ESTA DE LA CAMARA QUE NO HAY DIOS QUE ENTIENDA :)
local bolaHijaJug = scene:createObject("BolaHija")
local compTrBolaHijaJug = bolaHijaJug:addComponent('Transform')

compTrBolaHijaJug:sendMsg([[
     scale: 0.02,0.02,0.02;
     position: 0,10,0;
     rotation: 0,0,0;
 ]])

local rotarcam = bolaHijaJug:addComponent('CamRotate')

local camFollow = cam:addComponent('CamFollow')

camCamera:sendMsg([[
     name: escenaJuego;
     zOrder: -3;
 ]])
camCamera:sendMsg([[
     compositor: Posterize;
 ]])

playerMov:sendComponent(1, trcam)

trcam:sendComponent(1, compTrBolaHijaJug)

-- Metiendo componente rotar Camara
rotarcam:sendMsg([[
    verSens: 5.5
    horiSens: 5.5
]])

camFollow:sendComponent(0, tr)

rotarcam:sendGameObject(1, player)
rotarcam:sendGameObject(2, cam)

-------------------------------------YA SE ACABO NO SUFRAS MAS----------------------------------------------------------
----------COLOCAR OBJETOS ESCENARIO

-- Limites mundo --
-- MURO1
local muro1 = scene:createObject("muro1")
local muroTr1 = muro1:addComponent("Transform")
muroTr1:sendMsg([[
    scale: 1,10,350;
    position: -350,10,0;
    rotation: 0,0,0;
]])
local rBMuro1 = muro1:addComponent('Rigidbody')
rBMuro1:sendMsg([[
    trigger: false;
    state: kinematic;
    mass: 0.0;
    shape: cube;
    restitution: 0.9;
    colliderScale: 10,30,350;
]])

-- MURO2
local muro2 = scene:createObject("muro2")
local muroTr2 = muro2:addComponent("Transform")

muroTr2:sendMsg([[
    scale: 1,10,350;
    position: 350,10,0;
    rotation: 0,0,0;
]])

local rBMuro2 = muro2:addComponent('Rigidbody')
rBMuro2:sendMsg([[
    trigger: false;
    state: kinematic;
    mass: 0.0;
    shape: cube;
    restitution: 0.9;
    colliderScale: 10,30,350;
]])

-- MURO3
local muro3 = scene:createObject("muro3")
local muroTr3 = muro3:addComponent("Transform")

muroTr3:sendMsg([[
    scale: 350,10,1;
    position: 0,10,-350;
    rotation: 0,0,0;
]])

local rBMuro3 = muro3:addComponent('Rigidbody')
rBMuro3:sendMsg([[
    trigger: false;
    state: kinematic;
    mass: 0.0;
    shape: cube;
    restitution: 0.9;
    colliderScale: 350,30,10;
]])

-- MURO4
local muro4 = scene:createObject("muro4")
local muroTr4 = muro4:addComponent("Transform")

muroTr4:sendMsg([[
    scale: 350,10,1;
    position: 0,10,350;
    rotation: 0,0,0;
]])

local rBMuro4 = muro4:addComponent('Rigidbody')
rBMuro4:sendMsg([[
    trigger: false;
    state: kinematic;
    mass: 0.0;
    shape: cube;
    restitution: 0.9;
    colliderScale: 350,30,10;
]])

local trArbol1 = createArbol(arbol1, 350, 10, 200)
local trArbol2 = createArbol(arbol2, -350, 10, 200)
local trArbol3 = createArbol(arbol3, 350, 10, 60)
local trArbol4 = createArbol(arbol4, -350, 10, 60)
local trArbol5 = createArbol(arbol5, 200, 10, 350)
local trArbol6 = createArbol(arbol6, 200, 10, -350)
local trArbol7 = createArbol(arbol7, 60, 10, 350)
local trArbol8 = createArbol(arbol8, 60, 10, -350)
local trArbol9 = createArbol(arbol9, 350, 10, -200)
local trArbol10 = createArbol(arbol10, -350, 10, -200)
local trArbol11 = createArbol(arbol11, 350, 10, -60)
local trArbol12 = createArbol(arbol12, -350, 10, -60)
local trArbol13 = createArbol(arbol13, -200, 10, 350)
local trArbol14 = createArbol(arbol14, -200, 10, -350)
local trArbol15 = createArbol(arbol15, -60, 10, 350)
local trArbol16 = createArbol(arbol16, -60, 10, -350)

sceneboss1:createMesh("columna.mesh", -350, 10, 350, 10, 40, 10, 0, 0, 0)
sceneboss1:createMesh("columna2.mesh", 350, 10, -350, 10, 40, 10, 0, 0, 0)
sceneboss1:createMesh("columna3.mesh", -350, 10, -350, 10, 40, 10, 0, 0, 0)
sceneboss1:createMesh("columna3.mesh", 350, 10, 350, 10, 40, 10, 0, 0, 0)
sceneboss1:createRigidMesh("columna.mesh", 200, 10, 200, 10, 20, 10, 0, 0, 0)
sceneboss1:createRigidMesh("columna2.mesh", 100, 10, -100, 10, 20, 10, 0, 0, 0)
sceneboss1:createRigidMesh("columna3.mesh", -150, 10, -50, 10, 20, 10, 0, 0, 0)
sceneboss1:createRigidMesh("columna3.mesh", 250, 10, 100, 10, 20, 10, 0, 0, 0)
sceneboss1:createRigidMesh("columna.mesh", -100, 10, 100, 10, 20, 10, 0, 0, 0)
sceneboss1:createRigidMesh("columna2.mesh", -200, 10, -200, 10, 20, 10, 0, 0, 0)
sceneboss1:createRigidMesh("columna2.mesh", -270, 10, 0, 10, 20, 10, 0, 0, 0)
sceneboss1:createRigidMesh("columna2.mesh", 0, 10, -270, 10, 20, 10, 0, 0, 0)
sceneboss1:createMesh("wallRock1.mesh", 110, -5, 350, 5, 2, 3, 0, -0.7, 0)
sceneboss1:createMesh("wallRock1.mesh", 350, -5, 110, 5, 2, 3, 0, 0.85, 0)
sceneboss1:createMesh("wallRock2.mesh", 350, -5, -110, 5, 2, 3, 0, 1.6, 0)
sceneboss1:createMesh("wallRock1.mesh", -110, -5, -350, 5, 2, 3, 0, -0.7, 0)
sceneboss1:createMesh("wallRock2.mesh", -350, -5, 110, 5, 2, 3, 0, -1.6, 0)
sceneboss1:createMesh("wallRock1.mesh", -350, -5, 0, 5, 2, 3, 0, 0.85, 0)

sceneboss1:createCharco("Lodo", 1, 0, 2, 70)
sceneboss1:createCharco("Lodo", 1, -70, 2, -70)
sceneboss1:createCharco("Lodo", 1, 70, 2, -70)
---------------------------------------------------------------------------------------------------------------------------
-- -- -- -- JEFE -- -- -- --
local boss2 = scene:createObject("boss2")
local bossHealth = boss2:addComponent("Salud")
bossHealth:sendMsg([[
maxHealth: 100
]])
local bosstr = boss2:addComponent("Transform")
bosstr:sendMsg([[
scale: 0.02,0.02,0.02;
position: 30,30,-30;
rotation: 0,0,0;
]])

local sliderBehindLiveBoss = boss2:addComponent("Slider")
sliderBehindLiveBoss:sendMsg([[
materialBar: Heal;
materialBarBg: Heal_bg;
materialButton: CircleButton;
width: 1000;
height: 25;
posX: 135;
posY: 650;
]])

local sliderOverLiveBoss = boss2:addComponent("Slider")
sliderOverLiveBoss:sendMsg([[
materialBar: Heal;
materialBarBg: Heal_bg;
materialButton: CircleButton;
width: 1000;
height: 25;
posX: 135;
posY: 650;
]])

bossHealth:sendComponent(0, sliderOverLiveBoss);
bossHealth:sendComponent(1, sliderBehindLiveBoss);
playerAttack:sendComponent(1, bossHealth)

local bossAI = boss2:addComponent("BossDistancia")
bossAI:sendComponent(0, tr)
boss2:addComponent("Mesh"):sendMsg([[meshName: Boss2.mesh]])
local bossRb = boss2:addComponent('Rigidbody')
bossRb:sendMsg([[
state: dynamic;
mass: 100.0;
shape: sphere;
restitution: 0.0;
colliderScale: 18,18,18;
]])

playerMov:sendComponent(0, bossRb)
playerAttack:sendComponent(0, bosstr)
rotarcam:sendGameObject(0, boss2)

boss2:addComponent("Animation"):sendMsg([[animName: idle]])

---PARTICULAS JEFE AL TP---
local tpPrticle = scene:createObject("tpPrticle")
local trTpPrticle = tpPrticle:addComponent("Transform")
trTpPrticle:sendMsg([[scale: 1,1,1; position: 30,30,-30; rotation: 0,0,0;]])
local tpPrticleSys = tpPrticle:addComponent("ParticleSystem")
tpPrticleSys:sendMsg([[particleName: teleport; emitting: false]])
trTpPrticle:sendComponent(1, bosstr)
-------------------
local tpPrticle2 = scene:createObject("tpPrticle2")
local trTpPrticle2 = tpPrticle2:addComponent("Transform")
trTpPrticle2:sendMsg([[scale: 1,1,1; position: 30,35,-30; rotation: 0,0,0;]])
local tpPrticleSys2 = tpPrticle2:addComponent("ParticleSystem")
tpPrticleSys2:sendMsg([[particleName: magic; emitting: false]])
trTpPrticle2:sendComponent(1, bosstr)

end

return sceneboss2