


/*
**	Description	:	Set of API to initialise and use FIFO buffers
*/



/*
**	@brief				Function to read data from the buffer of a FIFO object.
**	@fifo(PARAM_IN)			Pointer to the FIFO object.
**	@data_read(PARAM_IN)		The pointer to the array to which the read data will be copied.
**	@bytes_count(PARAM_IN)		The number of bytes to be read from the buffer of the FIFO object.
*/
uint16_t Fifo_Read(struct FIFO_struct *fifo, uint8_t *data_read, const uint16_t bytes_count)
{
	/*	For operations	*/
	int16_t for_var;
	
	/*	For updation of buffer read pointer	*/
	int16_t next;
	
	/*	To return the number of bytes not read from the Fifo buffer	*/
	uint16_t bytesToRead = bytes_count;
	
	
	/*	Dont do anything and return, if the buffer points to NULL(i.e if the fifo object was not initialised)	*/
	if (!fifo->buffer)
		return bytesToRead;
	
	/*	Perform the read operations read one byte each time	*/
	for (for_var = 0; for_var < bytes_count; for_var ++)
	{
		if (Fifo_bufferIsEmpty(fifo))
			return bytesToRead;
		
		/*	Read one byte from the Fifo buffer at the read position	*/
		*(data_read + (bytes_count - bytesToRead)) = fifo->buffer[fifo->head];
		
		/*	Update the position where the next read has to be performed	*/
		next  = (fifo->head+1)%fifo->size;
		
		/*	If the buffer has emptied after reading the byte	*/
		if (fifo->head == fifo->tail)
		{
			/*	Flush the Fifo buffer	*/
			Fifo_Flush(fifo);
		}
		/*	If the fifo buffer has not emptied after reading the byte	*/
		else
		{
			/*	Update the next read position in the Fifo buffer	*/
			fifo->head = next;
		}
		
		
		/*	Update the number of bytes remaining to be read	*/
		--bytesToRead;
		
	}
	
	return bytesToRead;
}



/*
**	@brief										Function to write data into the buffer of a FIFO object.
**	@fifo(PARAM_IN)						Pointer to the FIFO object.
**	@data_to_write(PARAM_IN)	The pointer to the array containing the data to be written to the buffer
**	@bytes_count(PARAM_IN)		The number of bytes to be written the buffer of the FIFO object.
*/
uint16_t Fifo_Write(struct FIFO_struct *fifo, const uint8_t *data_to_write, const uint16_t bytes_count)
{
	/*	For operations	*/
	int16_t for_var;
	
	/*	For updation of buffer write pointer	*/
	int16_t next;
	
	/*	To return the number of bytes not written to the Fifo buffer	*/
	uint16_t bytesToWrite = bytes_count;
	
	
	/*	Dont do anything and return, if the buffer points to NULL(i.e if the fifo object was not initialised)	*/
	if (!fifo->buffer)
		return bytesToWrite;
	
	/*	Perform the write operations to write one byte each time	*/
	for (for_var = 0; for_var < bytes_count; for_var ++)
	{
		/*	Position where the present write has to be performed	*/
		next  = (fifo->tail+1)%fifo->size;
		
		if (Fifo_bufferIsFull(fifo))
		{
			return bytesToWrite;
		}
		
		/*	Update the write position in the Fifo buffer	*/
		fifo->tail = next;
		
		/*	Write one byte into the Fifo buffer at the updated write position	*/
		fifo->buffer[next] = *(data_to_write + (bytes_count - bytesToWrite));
		
		/*	Update the number of bytes remaining to be written	*/
		--bytesToWrite;
		
		/*	Indicate that the Fifo buffer is not empty	*/
		if (fifo->head == -1)
			fifo->head = 0;
	}
	
	return bytesToWrite;
}


/*
**	@brief						Function to check if the buffer of a FIFO object if empty.
**	@pFifo(PARAM_IN)				Pointer to the FIFO object(structure).
*/
bool Fifo_bufferIsEmpty(const struct FIFO_struct *pFifo)
{
	if (pFifo->head < 0)
		return true;			/*	Buffer is empty	*/
	else
		return false;			/*	Buffer is not empty	*/
}


/*
**	@brief						Function to check if the buffer of a FIFO object if full.
**	@pFifo(PARAM_IN)				Pointer to the FIFO object(structure).
*/
bool Fifo_bufferIsFull(const struct FIFO_struct *pFifo)
{
	int16_t next;
	
	next = (pFifo->tail+1)%pFifo->size;
	
	if (next == pFifo->head)
		return true;			/*	Buffer is Full	*/
	else
		return false;			/*	Buffer is not Full	*/
}


/*
**	@brief						Function to prepare a FIFO object for functioning.
**	@pFifo(PARAM_IN)				Pointer to the FIFO object(structure).
**	@size(PARAM_IN)					The size of the buffer of the FIFO object.
*/
void Fifo_Init(struct FIFO_struct *pFifo, const uint8_t size)
{
	pFifo->head = -1;																			
	pFifo->tail = -1;
	pFifo->size = size;
	pFifo->buffer = malloc(size*(sizeof(uint8_t)));	/*	Dynamic allocation for buffer	*/
}


/*
**	@brief						Function to discard a FIFO object.
**	@pFifo(PARAM_IN)				Pointer to the FIFO object(structure).
**	@size(PARAM_IN)					The size of the buffer of the FIFO object.
*/
void Fifo_DeInit(struct FIFO_struct *pFifo)
{
	pFifo->head = -1;																			
	pFifo->tail = -1;
	pFifo->size = 0;				/*	Indicate the size of the FIFO buffer to be zero	*/
	free(pFifo->buffer);				/*	Free the memory reserved by the FIFO buffer	*/
	pFifo->buffer = NULL;				/*	Null the buffer pointer	*/
}


/*
**	@brief				Function to put read and write pointers of Fifo buffer to their initial states.
**	@pFifo(PARAM_IN)		Pointer to the FIFO object(structure).
*/
void Fifo_Flush(struct FIFO_struct *pFifo)
{
	pFifo->head = -1;																			
	pFifo->tail = -1;
}
