function resetMagnets () {
	for (i = 0;i < magnet.length;i++) {
		magnet[i].style.top = 25 + (Math.random() * (document.body.clientHeight - 50));
		magnet[i].style.left = 50 + (Math.random() * 275);
	}
}