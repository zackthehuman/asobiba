function update(dt) {
    //if(emitParticle) {
        if(particleSystem) {
            local particle = Particle();
            particle.size = 50;

            local position = Vector2f();
            position.x = ::width / 2; // mouseX;
            position.y = ::height / 2; // mouseY;
            particle.position = position;

            local velocity = Vector2f();
            velocity.x = (rand() % 200) - 100;
            velocity.y = (rand() % 200) - 100;
            particle.velocity = velocity;

            particleSystem.add(particle);
        }
    //}

    if(particleSystem) {
        particleSystem.update(dt);
    }
}