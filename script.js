const config = {
	width: 1400,
	height: 750,
	backgroundColor: "#FFFFF"
	parent: "gameContainer",
	scene: [GameScene],
	physics: {
		defauld: "arcade"
	}
};

class GameScene extends Phaser.Scene {
	