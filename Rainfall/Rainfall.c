// AngryAnt's reworking of the Adafruit Sample Code.

#define RAIN_MIN 2
#define RAIN_MAX 10
#define RAIN_CLAMP(var) var = ((var - RAIN_MIN) % (RAIN_MAX - RAIN_MIN)) + RAIN_MIN
#define RAIN_BEFORE 0
#define RAIN_IN 1
#define RAIN_AFTER 2

void Rainfall (uint8_t wait, uint_8 dropSpeed, uint8_t dropLength, bool direction)
{
	int head, tail, update;

	// Initial head & tail based on direction - also set the update value
	if (direction)
	{
		head = RAIN_MIN;
		tail = RAIN_MIN + dropLength;
		update = 1;
	}
	else
	{
		head = RAIN_MAX - dropLength;
		tail = RAIN_MAX;
		update = -1;
	}

	// Run forever
	unsigned long lastTime = 0;
	while (true)
	{
		// Update LEDs if necessary
		unsigned long currentTime = millis ();
		if (currentTime - lastTime > dropSpeed)
		{
			lastTime = currentTime;

			// Move head & tail
			head += update;
			tail += update;
			RAIN_CLAMP (head);
			RAIN_CLAMP (tail);
	
			// Calculate the actual span needing light and set as starting before that span
			int
				from = min (head, tail),
				to = max (head, tail),
				rainPosition = RAIN_BEFORE;
	
			// Run the active rain LED span
			for (int ledIndex = RAIN_MIN; ledIndex <= RAIN_MAX;)
			{
				// If we were before the start of the drop, see if we are in the drop now, mark as such and continue
				if (rainPosition == RAIN_BEFORE)
				{
					if (ledIndex >= from)
					{
						rainPosition = RAIN_IN;
						continue;
					}
				}
				// If we were in the drop, see if we moved out of it - otherwise turn on the LED and continue
				else if (rainPosition == RAIN_IN)
				{
					if (ledIndex >= to)
					{
						rainPosition = RAIN_AFTER;
					}
					else
					{
						strip.setPixelColor (ledIndex++, 0, 0, 255, 0);
						continue;
					}
				}
	
				// We are before or after the rain, so we turn off the LED
				strip.setPixelColor (ledIndex++, 0, 0, 0, 25);
			}

			strip.show ();
		}

		delay (wait);
	}
}