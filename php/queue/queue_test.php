<?php

	include __DIR__ . '/queue.php';
	$queue = new queue('queue_job');
	
	include __DIR__ . '/job.php';
	$job_0 = new job;
	$job_1 = new job;

	$job_0->name = 'job_0';
	$job_0->proc = function () {
		fwrite(STDOUT, "this is job_0\n");
		return 0;
	};
	
	$job_1->name = 'job_1';
	$job_1->proc = function () {
		fwrite(STDOUT, "this is job_1\n");
		return 0;
	};
	
	$queue->push($job_0);
	$queue->push($job_1);

	return 0;
?>
