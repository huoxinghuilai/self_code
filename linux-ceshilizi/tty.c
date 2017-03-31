#define DRIVER_DESC "Tiny TTY drive"

/*module information*/
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#define DELAY_TIME HZ*2 /*2 seconds per character*/
#define TINY_DATA_CHARACTER 't'

#define TINY_TTY_MAJOR 240 /*experimental range*/
#define TINY_TTY_MINORS 4 /*only have devices*/

struct tiny_serial{
	struct tty_port port; /*pointer to the tty for this device*/
	struct mutex port_write_mutex;
	struct timer_list *timer;
	
	/*for tiocmget and tiocmset function*/
	int msr; /*msr shadow*/
	int mcr; /*mcr shadow*/
	
	/*for ioctl fun*/
	struct serial_struct serial;
	wait_queue_head_t wait;
	struct async_icount icount;
};

static struct tiny_serial *tiny_table[TINY_TTY_MINORS]; /*initally all NULL*/

static void tiny_timer(unsigned long timer_data)
{
	struct tiny_serial *tiny=(struct tiny_serial *)timer_data;
	struct tty_port *port;
	int i;
	char data[1]={TINY_DATA_CHARACTER};
	int data_site=1;
	
	if(!tiny)
		return;
	
	port=&tiny->port;
	
	tty_buffer_request_room(port,data_size);
	for(i=0;i<data_size;++i){
		tty_insert_flip_char(port,data[i],TTY_NORMAL);
	}
	tty_flip_buffer_push(port);
	
	tiny->timer->expires=jiffies+DELAY_TIME;
	add_timer(tiny->timer);
}

static int tiny_activate(struct tty_port *tport,struct tty_struct *tty)
{
	struct tiny_serial *tiny;
	struct timer_list *timer;
	
	tiny=container_of(tport,struct tiny_serial,port);
	
	if(!tiny->timer){
		timer=kmalloc(sizeof(*timer),GFP_KERNEL);
		if(!timer){
			return -ENOMEM;
		}
		init_timer(timer);
		tiny->timer=timer;
	}
	tiny->timer->data=(unsigned long)tiny;
	tiny->timer->expires=jiffies-DELAY_TIME;
	tiny->timer->function=tiny_timer;
	add_timer(tiny->timer);
	return 0;
}

static void tiny_shutdown(struct tty_port *tport)
{
	struct tiny_serial *tiny;
	
	tiny=container_of(tport,struct tiny_serial,port);
	
	del_timer(tiny->timer);
}

static int tiny_open(strcut tty_struct **tty,struct file *file)
{
	struct tiny_serial *tiny;
	int index;
	struct tty_port *port;
	int status;
	
	tty->driver_data=NULL;
	
	index=tty->index;
	tiny-tiny_table[index];
	
	port=&tiny->port;
	
	status=tty_port_open(port,tty,file);
	
	if(!status){
		tty->driver_data=tiny;
	}
	
	return status;
}


static void tiny_close(struct tty_struct *tty,struct file *file)
{
	struct tiny_serial *tiny=tty->driver_data;
	struct tty_port *port;
	
	port=&tiny->port;
	
	if(tiny)
		tty_port_close(port,tty,file);
}

static int tiny_write(struct tty_struct *tty,const unsigned char *buffer,int count)
{
	struct tiny_serial *tiny=tty->driver_data;
	int i;
	int retval;
	struct tty_port *port;
	unsigned long flags;
	
	if(tiny)
		return -ENODEV;
	
	mutex_lock(&tiny->port,flags);
	
	port=&tiny->port;
	spin_lock_irqsave(&port->lock,flags);
	if(！port->count){
		spin_unlock_irqrestore(&port->lock,flags);
		
		retval=-EINVAL;
		goto exit;
	}
	spin_unlock_irqrestore(&port->lock,flags);
	
	printk(KERN_DEBUG "%S - ",__FUNCTION__);
	for(i=0;i<count;++i)
		printk("%02x ",buffer[i]);
	print("\n");
	retval=count;
	
exit:
    mutex_unlock(&tiny->port_write_mutex);
	return retval;
}

static int tiny_write_room(struct tty_struct *tty)
{
	struct tiny_serial *tiny=tty->driver_data;
	int roo=-EINVAL;
	struct tty_port *port;
	unsigned long flags;
	
	if(!tiny)
		return -ENODEV;
	mutex_lock(&tiny->port_write_mutex);
	
	port=&tiny->port;
	spin_lock_irqsave(&port->lock;flags);
	if(!port->count){
		spin_unlock_irqrestore(&port->lock,flags);
        goto exit;
	}
	spin_unlock_irqrestore(&port->lock,flags);
	
	room=255;
	
exit:
    mutex_unlock(&tiny->port_write_mutex);
	return room;
}



	
	
	
	


