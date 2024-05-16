window.onload = function() {
    var config = {
        type: Phaser.AUTO,
        width: 320,
        height: 480,
        parent: 'gameContainer',
        physics: {
            default: 'arcade',
            arcade: {
                gravity: { y: 300 },
                debug: false
            }
        },
        scene: {
            preload: preload,
            create: create,
            update: update
        }
    };

    var game = new Phaser.Game(config);
    var bird;
    var pipes;
    var pipeSpacing = 750;
    var pipeHole = 120;
    var cursors;
    var lastPipeTime = 0;

    function preload() {
        this.load.image('sky', skyImage);
        this.load.image('bird', birdImage);
        this.load.image('pipe', pipeImage);
    }

    function create() {
        // Add sky background
        this.add.image(160, 240, 'sky');
        
        // Add bird
        bird = this.physics.add.sprite(50, 240, 'bird');
        bird.setGravityY(100);
    
        // Add pipes group
        pipes = this.physics.add.group();
    
        // Handle input
        cursors = this.input.keyboard.createCursorKeys();
    
        // Setup collision between the bird and the pipes
        this.physics.add.collider(bird, pipes, gameOver, null, this);
    }
    
    function update(time, delta) {
        // Bird flap control
        if (cursors.space.isDown) {
            bird.setVelocityY(-180);
        }
        
        // Generate pipes
        if (time > lastPipeTime + pipeSpacing) {
            var centerY = 280; // Middle of the screen height
            var minGapHalf = 80; // Minimum half-gap size
            var maxGapHalf = 160; // Maximum half-gap size
            var gapHalf = Math.floor(Math.random() * (maxGapHalf - minGapHalf + 1) + minGapHalf); // Randomize the gap half size
    
            // Calculate positions for upper and lower pipes
            var upperPipeY = centerY - gapHalf + 100; // Upper pipe top edge
            var lowerPipeY = centerY + gapHalf; // Lower pipe top edge
            
            // Create upper pipe, flipped vertically
            var upperPipe = pipes.create(320, upperPipeY, 'pipe');
            upperPipe.setImmovable(true);
            upperPipe.body.allowGravity = false;
            upperPipe.setVelocityX(-200);
            upperPipe.setFlipY(true); // Flip the pipe vertically
    
            // Adjust the y position after flipping to align the pipe's bottom edge correctly
            upperPipe.y -= upperPipe.displayHeight;
    
            // Create lower pipe
            var lowerPipe = pipes.create(320, lowerPipeY, 'pipe');
            lowerPipe.setImmovable(true);
            lowerPipe.body.allowGravity = false;
            lowerPipe.setVelocityX(-200);
            
            lastPipeTime = time;
        }
    
        // Remove pipes that are no longer visible
        pipes.getChildren().forEach(function(pipe) {
            if (pipe.x < -50) {
                pipes.remove(pipe, true, true);
            }
        });
    
        // Restart game if bird falls off
        if (bird.y > 480 || bird.y < 0) {
            restartGame();
        }
    }       
    
    function gameOver(bird, pipe) {
        // Handle what happens when the bird collides with a pipe
        console.log('Game Over!'); // Log game over message (for debugging)
        restartGame(); // Call restartGame to reset the scene
    }
    
    function restartGame() {
        // Reset bird's position
        bird.setX(50);
        bird.setY(240);
    
        // Reset bird's velocity
        bird.setVelocity(0, 0); // Resets both x and y velocity
    
        // Reset bird's angular velocity and rotation if needed
        bird.setAngularVelocity(0);
        bird.setRotation(0);
    
        // Clear all pipes
        pipes.clear(true, true);
    
        // Optionally, re-enable bird's physics body if it was disabled
        bird.body.enable = true;
    
        // Reset timer for pipe generation
        lastPipeTime = 0;
    }
    
    
};
