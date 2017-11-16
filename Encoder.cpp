
Encoder::Encoder(int pinA, int pinB)
{
	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);
	
	this->A = pinA;
	this->B = pinB;
}

int Encoder::getTicks()
{
	return this->ticks;
}

void Encoder::process()
{
	if(digitalRead(A) == digitalRead(B))
  	{
    	++ticks;
  	}
  	else
  	{
    	--ticks;
	}
}

void Encoder::reset()
{
	ticks = 0;	
}