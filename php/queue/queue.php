<?php
	
	class queue {
		public $queue_name;

		public function __construct($str) {
			$this->queue_name = $str;
		}

		public function push(job $job) {
			$path = __DIR__ . '/Job/' . $this->queue_name . '/';
			
			if (!is_dir($path)) {
				mkdir($path, 0777, true);
			}

			$path = $path . $job->name . '.txt';

			$fp = fopen($path, "w");
			fwrite($fp, $job->name, strlen($job->name));
			fclose($fp);

			if (pcntl_fork() == 0) {
				
				while(1) {
					$fp = fopen($path, "r");
					$str = fgets($fp);
					fclose($fp);
					if (!strcmp($str, 'execute')) {
						unlink($path);
						return ($job->proc)();
					}
				}
			}
		}

		public function listen() {
			$dir = __DIR__ . '/Job/' . $this->queue_name . '/';
			$dh = dir($dir);

			while ($fp = $dh->read()) {
				$path = $dh->path . $fp; 
				
				$fp = fopen($path, "w");
				fwrite($fp, 'execute', strlen('execute'));

				sleep(3);
			} 
		}
	}
?>
