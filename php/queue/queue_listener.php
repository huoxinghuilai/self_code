<?php
	include __DIR__ . '/queue.php';

	$queue = new queue('queue_job');
	
	$queue->listen();
?>
