
local menu = {}


function menu:createMainMenu()
    scene:name("Main menu")
    local screenwidth = width();
    local screenheight = height();


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
        width: ]] .. screenwidth .. [[;
        height : ]] .. screenheight .. [[;
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
        posY: -]] .. screenheight .. [[;
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
        width: ]] .. screenwidth .. [[;
        height :]] .. screenheight .. [[;
        posZ: 19
    ]])


    createVignette();
    --Blueprint.spawnObject(scene, "Vignette")
end

function menu:createSettings()
    scene:name("Settings")

    local container = menu:createRightContainer()

    local scroll = scene:createObject('Scroll'):addComponent('Scroll'):sendMssg([[
        minHeight: 0;
        maxHeight: 720;
        automatic: false;
        speed: 100;
        posX: 0;
        posY: 52;
        posZ: 0;
        timeToEnable: 2.0;
    ]])
    scroll:sendComponent(-1, container)
    container:sendComponent(0, scroll);


    scroll:sendComponent(0, menu:createImage('mainmenuBackgroundImage', 10, 10, 11, 400, 400))

    local settings = scene:createObject('Settings'):addComponent('Settings'):sendMssg([[
        resolution: 1920, 1080, 0
    ]])
    settings:sendMssg([[
        resolution: 1280, 720, 0
    ]])
    settings:sendMssg([[
        resolution: 852, 480, 0
    ]])

    local fullscreenbutton = menu:createButton('mainmenuButton', 20, 420, 12, 200, 50)
    scroll:sendComponent(0, fullscreenbutton)
    settings:sendComponent(1, fullscreenbutton);

    
    local p1080 = menu:createButton('mainmenuButton', 20, 470, 12, 200, 50)
    scroll:sendComponent(0, p1080)
    settings:sendComponent(-1, p1080);

    
    local p720 = menu:createButton('mainmenuButton', 20, 530, 12, 200, 50)
    scroll:sendComponent(0, p720)
    settings:sendComponent(-2, p720);

    
    local p480 = menu:createButton('mainmenuButton', 20, 590, 12, 200, 50)
    scroll:sendComponent(0, p480)
    settings:sendComponent(-3, p480);
    
    
    local p480 = menu:createButton('mainmenuButton', 20, 650, 12, 200, 50)
    scroll:sendComponent(0, p480)
    settings:sendComponent(0, p480);

end

function menu:createCredits()
    scene:name("Credits")

    local container = menu:createRightContainer()

    local scroll = scene:createObject('Scroll'):addComponent('Scroll'):sendMssg([[
        minHeight: 0;
        maxHeight: 720;
        automatic: true;
        speed: 100;
        posX: 0;
        posY: 52;
        posZ: 0;
        timeToEnable: 2.0;
    ]])
    scroll:sendComponent(-1, container)
    container:sendComponent(0, scroll);



    scroll:sendComponent(0, menu:createImage('mainmenuBackgroundImage', 10, 10, 11, 400, 400))
    --createImage('mainmenuBackgroundImage', 590, 10, 4, 400, 400)

    scroll:sendComponent(0, menu:createTextElement('Creditos de mi jueguito', 200, 450, 12, 0.05, 0));
end


function menu:createAbout()
    scene:name("About")

    local container = menu:createRightContainer()

    local scroll = scene:createObject('Scroll'):addComponent('Scroll'):sendMssg([[
        minHeight: 0;
        maxHeight: 720;
        automatic: false;
        speed: 100;
        posX: 0;
        posY: 52;
        posZ: 0;
        timeToEnable: 2.0;
    ]])
    scroll:sendComponent(-1, container)

    container:sendComponent(0, scroll);
    scroll:sendComponent(0, menu:createImage('mainmenuBackgroundImage', 10, 10, 11, 400, 400))


    
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


function menu:createRightContainer()
    
    local w = 600;
    local xposition = width() - w - 100;

    local containerObj = scene:createObject("Container")
    containerObj:addComponent('MoveUI'):sendMssg([[
        destination: ]] .. xposition ..[[, 0, 0;
        duration: 2.0;
        enabled: true;
    ]])

    local container = containerObj:addComponent("UIContainer")
    container:sendMssg([[
        posX: ]] .. xposition .. [[;
        posY: -720;
        posZ: 0;
    ]])

    container:sendComponent(0, menu:createImage('mainmenuBanner', 0, 52, 10, 600, 640));
    return container
end

function menu:createImage(material, x, y, z, w, h)
    return scene:createObject(material):addComponent('Image'):sendMssg([[
        material: ]] .. material .. [[;
        height:  ]] .. h .. [[;
        width :  ]] .. w .. [[;
        posX: ]] .. x .. [[;
        posY: ]] .. y .. [[;
        posZ: ]] .. z)
end

function menu:createButton(material, x, y, z, w, h)

    return scene:createObject('Button:' .. material):addComponent('Button'):sendMssg([[
        material:  ]] .. material..[[;
        width:  ]] .. w ..[[;
        height: ]] .. h ..[[;
        posX:   ]] .. x ..[[;
        posY:   ]] .. y ..[[;
        posZ:   ]] .. z ..[[;
    ]])

end

function menu:createTextElement(text, x, y, z, size, alignment)
    return scene:createObject("textObj"):addComponent("Text"):sendMsg([[
        posX: ]] .. x .. [[;
        posY: ]] .. y .. [[;
        posZ: ]] .. z .. [[;
        fontName: SourceSansProLight
        mainColor: 1, 1, 1, 1.0;
        textScale: ]] .. size ..[[;
        alignment : ]] .. alignment .. [[;
        text: #]] .. text .. [[#;
        ]])
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

        local screenwidth = width();
        local screenheight = height();

        local continue = scene:createObject("Start Button"):addComponent("Button");
        local exitButton = scene:createObject("Exit Button"):addComponent("Button");
        local banner = scene:createObject("Banner"):addComponent("Image");
        local logo = scene:createObject("Logo"):addComponent("Image");

        logo:sendMsg([[
            material: logo;
            width: 247;
            height : 133;
            posX: 535;
            posY: 150
            posZ: 2
        ]])

        banner:sendMsg([[
            material: mainmenuBanner;
            width: 300;
            height : ]] .. screenheight .. [[;
            posX: 510;
            posZ: 1
        ]])

        continue:sendMsg([[
            material: backtogame;
            width: 200;
            height: 60;
            posX: 560;
            posY: 480;
            posZ: 2
        ]])

        exitButton:sendMsg([[
            material: backtomenu;
            width: 200;
            height: 60;
            posX: 560;
            posY: 550;
            posZ: 2
        ]])

        local menuObj = scene:createObject("Pause Component"):addComponent("PauseMenu")
        menuObj:sendComponent(0, continue);
        menuObj:sendComponent(1, exitButton);
    end
}
end

return menu