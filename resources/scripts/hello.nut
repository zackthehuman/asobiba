::print("Hello from Squirrel land!");

srand(1337);

// Globals
emitParticle <- false;
particleSystem <- false;
mouseX <- 0;
mouseY <- 0;

function testBindings() {
    local vec = Vector2f();
    vec.x = 45;
    vec.y = 77;

    ::print(vec);
    ::print(vec.x);
    ::print(vec.y);

    local color = Color();
    color.setR(128);
    color.setG(128);
    color.setB(128);

    ::print(color);
    ::print(color.getR());
}

testBindings();

function handleEvent(event) {
    ::print(event.type);
}