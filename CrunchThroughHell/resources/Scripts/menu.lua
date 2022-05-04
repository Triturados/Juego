
local menu = {}


function menu:createMainMenu()
    scene:name("Main menu")
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
        duration: 2.0;
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
        height: 640;
        width : ]].. bannerwidth .. [[;
        posX: 0;
        posY: 52
        posZ: ]] .. zOrder ..[[
    ]]))
    zOrder = zOrder + 1

    container:sendComponent(0, scene:createObject("Logo"):addComponent("Image"):sendMsg([[
        material: logo;
        width: 247;
        height : 133;
        posX: ]] .. round((bannerwidth - 247) * 0.5) ..[[;
        posY: 150
        posZ: ]] .. zOrder ..[[
    ]]))
    zOrder = zOrder + 1



    local halfwidth = round((width() - 371) * 0.5);
    local pressKeyHeight = round(height() * 0.5 + 100);
    local presskey = scene:createObject("Press any key"):addComponent("Image"):sendMsg([[
        material: mainmenuPressKey;
        width: 371;
        height : 29;
        posX: ]] .. halfwidth .. [[;
        posY: ]] .. pressKeyHeight .. [[;
        posZ: ]] .. zOrder ..[[
    ]])
    zOrder = zOrder + 1


    local mainmenu = bg:addComponent("MainMenu");
    local initialHeigh = 320
    for i = 0, 6, 1 do
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

    mainmenu:sendComponent(-2, createArrow(height() - 60, 'mainmenuArrowDown'))
    mainmenu:sendComponent(-1, createArrow(426, 'mainmenuArrow'))
    mainmenu:sendComponent(-3, presskey);
    mainmenu:sendMssg('centerX: 250');

    local hideposition = round((bannerwidth - 256)* 0.5);
    container:sendComponent(0, scene:createObject("Hide"):addComponent("Image"):sendMsg([[
        material: mainmenuHide;
        width: 256;
        height : 72;
        posX: ]] .. hideposition .. [[;
        posY: 310
        posZ: ]] .. zOrder ..[[
    ]]))
    zOrder = zOrder + 1

    scene:createObject("Black border"):addComponent("Image"):sendMsg([[
        material: mainmenuBlackBorder;
        width: 1280;
        height : 720;
        posZ: ]] .. zOrder ..[[
    ]])
    zOrder = zOrder + 1

    Blueprint.spawnObject(scene, "Vignette")
end

function menu:createSettings()
    scene:name("Settings")

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

end

function menu:createCredits()
    scene:name("Credits")

    local container = createRightContainer()

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


function createRightContainer()
    
    local containerObj = scene:createObject("Container")
    containerObj:addComponent('MoveUI'):sendMssg([[
        destination: 100, 0, 0;
        duration: 2.0;
        enabled: true;
    ]])

    local container = containerObj:addComponent("UIContainer")
    container:sendMssg([[
        posX: 400;
        posY: -720;
        posZ: 0;
    ]])

    container:sendComponent(0, scene:createObject("Banner"):addComponent("Image"):sendMsg([[
        material: mainmenuBanner;
        height: 640;
        width : 600;
        posX: 0;
        posY: 52
        posZ: 0;
    ]]))
    return container
end


function menu:menuPausa()
    return {
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
end

return menu