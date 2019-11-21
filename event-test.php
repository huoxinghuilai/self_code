<?php
	/*
	 * namespace home\csmpadmin\event;
	 *
	 * use home\csmpadmin\event\event;
	 * use home\csmpadmin\event\job;
	 */

	include __DIR__ . '/event.php';
	$event = new event;

	include __DIR__ . '/job.php';
	$job_0 = new job;
	$job_1 = new job;

	$job_0->name = 'event_0';
	
	$job_1->name = 'event_1';
	$job_1->proc = function () {
		$str = 'you have trigger the event!';
		echo $str;
		echo "\n";
		return 0;
	};

	$event->on($job_0);
	$event->on($job_1);

	$event->trigger($job_1->name);

	return 0;
?>
