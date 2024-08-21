int KYOBPM = 174;

void expandingCube(int d)
{
  int col = 0;
  int min, max, b1, b2;
  bool light = false;
  for (int i = 3; i >= 0; i--) // 4 cubes, 2,4,6,8 cubed
  {
    min = 0 + i;
    max = 7 - i;
    // Light LED when it is along one of the 3 axis within the bounds
    // x: (col == min || col == max) && (row >= min && row <= max)
    // y: (row == min || row == max) && (col >= min && col <= max)
    // z: (lev == min || lev == max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        for (int col = 0; col <= 7; col++)
        {
          /*if ((lev == min || lev == max) && (((col == min || col == max) && (row >= min && row <= max)) || ((row == min || row == max) && (col >= min && col <= max))))
          {
            LED(lev,row,col,15,0,0);
          }*/
          if (((lev == min || lev == max) && (col == min || col == max) && (row >= min && row <= max)) ||
              ((lev == min || lev == max) && (row == min || row == max) && (col >= min && col <= max)) ||
              ((lev >= min && lev <= max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))))
              {
                LED(lev,row,col,15,0,0);
              }
        }
      }
    }
    delay(d);
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        for (int col = 0; col <= 7; col++)
        {
          /*if ((lev == min || lev == max) && (((col == min || col == max) && (row >= min && row <= max)) || ((row == min || row == max) && (col >= min && col <= max))))
          {
            LED(lev,row,col,0,0,0);
          }*/
          if (((lev == min || lev == max) && (col == min || col == max) && (row >= min && row <= max)) ||
              ((lev == min || lev == max) && (row == min || row == max) && (col >= min && col <= max)) ||
              ((lev >= min && lev <= max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))))
              {
                LED(lev,row,col,0,0,0);
              }
        }
      }
    }
  }
}

void contractingCube(int d)
{
  int col = 0;
  int min, max, b1, b2;
  bool light = false;
  for (int i = 0; i <= 3; i++) // 4 cubes, 2,4,6,8 cubed
  {
    min = 0 + i;
    max = 7 - i;
    // Light LED when it is along one of the 3 axis within the bounds
    // x: (col == min || col == max) && (row >= min && row <= max)
    // y: (row == min || row == max) && (col >= min && col <= max)
    // z: (lev == min || lev == max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        for (int col = 0; col <= 7; col++)
        {
          /*if ((lev == min || lev == max) && (((col == min || col == max) && (row >= min && row <= max)) || ((row == min || row == max) && (col >= min && col <= max))))
          {
            LED(lev,row,col,15,0,0);
          }*/
          if (((lev == min || lev == max) && (col == min || col == max) && (row >= min && row <= max)) ||
              ((lev == min || lev == max) && (row == min || row == max) && (col >= min && col <= max)) ||
              ((lev >= min && lev <= max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))))
              {
                LED(lev,row,col,15,0,0);
              }
        }
      }
    }
    delay(d);
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        for (int col = 0; col <= 7; col++)
        {
          /*if ((lev == min || lev == max) && (((col == min || col == max) && (row >= min && row <= max)) || ((row == min || row == max) && (col >= min && col <= max))))
          {
            LED(lev,row,col,0,0,0);
          }*/
          if (((lev == min || lev == max) && (col == min || col == max) && (row >= min && row <= max)) ||
              ((lev == min || lev == max) && (row == min || row == max) && (col >= min && col <= max)) ||
              ((lev >= min && lev <= max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))))
              {
                LED(lev,row,col,0,0,0);
              }
        }
      }
    }
  }
}

void expandingSquare(int col)
{
  //int col = 0;
  int lowerBound, upperBound, b1, b2;
  bool light = false;
  for (int i = 3; i >= 0; i--) // 4 cubes, 2,4,6,8 cubed
  {
    lowerBound = 0 + i;
    upperBound = 7 - i;
    // Light LED:
    // if lev == bound, light inbetween bound
    // else, light only at bounds
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        if (lev == lowerBound || lev == upperBound)
        {
          // light between
          if (row >= lowerBound && row <= upperBound)
          {
            LED(lev,row,col,15,0,0);
          }
        }
        else if (lev > lowerBound && lev < upperBound)
        {
          if ((row == lowerBound || row == upperBound))
          {
            LED(lev,row,col,15,0,0);
          }
        }
      }
    }
    delay(100);
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        if (lev == lowerBound || lev == upperBound)
        {
          // light between
          if (row >= lowerBound && row <= upperBound)
          {
            LED(lev,row,col,0,0,0);
          }
        }
        else if (lev > lowerBound && lev < upperBound)
        {
          if ((row == lowerBound || row == upperBound))
          {
            LED(lev,row,col,0,0,0);
          }
        }
      }
    }
  }
}

void intro()
{
  int numNotes = 18;
  int lev, row, col, waitTime;
  byte* randomColor;
  for (int i = 1; i <= numNotes; i++)
  {
    lev = random(8);
    row = random(8);
    col = random(8);
    if (i % 2 == 0)
    {
      randomColor = FUCHSIA;
    }
    else
    {
      randomColor = LIME;
    }
    if (i <= 5 && i >= 3)
    {
      waitTime = 172;
    }
    else
    {
      waitTime = 344;
    }
    LED(lev,row,col,randomColor[0],randomColor[1],randomColor[2]);
    timer(waitTime);
    LED(lev,row,col,0,0,0);
  }
}

void Explode(int numParticles, int delayx) {
  clean();

  int i, f, e, x;

  float origin_x = 4;
  float origin_y = 4;
  float origin_z = 5;

  int rand_y, rand_x, rand_z;

  float slowrate, gravity;

  // Particles and their position, x,y,z and their movement, dx, dy, dz
  float particles[numParticles][6];
  float lastpart[numParticles][3];

  /*origin_x = rand() % 4;
  origin_y = rand() % 4;
  origin_z = rand() % 2;
  origin_z +=5;
  origin_x +=2;
  origin_y +=2;*/
  //byte* randColor = colors[random(13)];
  //int r = color[0];
  //int g = color[1];
  //int b = color[2];
  byte* color;

  // Fill particle array
  for (f=0; f < numParticles; f++) {
    // Position
    particles[f][0] = origin_x;
    particles[f][1] = origin_y;
    particles[f][2] = origin_z;

    rand_x = rand() % 200;
    rand_y = rand() % 200;
    rand_z = rand() % 200;

    // Movement
    particles[f][3] = 1 - (float)rand_x / 100; // dx
    particles[f][4] = 1 - (float)rand_y / 100; // dy
    particles[f][5] = 1 - (float)rand_z / 100; // dz
  }

  // explode
  for (e=0; e < 25; e++) {
    slowrate = 1 + tan((e + 0.1) / 20) * 10;
    gravity = tan((e + 0.1) / 20) / 2;


    for (f=0; f < numParticles; f++) {
      particles[f][0] += particles[f][3] / slowrate;
      particles[f][1] += particles[f][4] / slowrate;
      particles[f][2] += particles[f][5] / slowrate;
      particles[f][2] -= gravity;

      if (f % 2 == 0)
      {
        color = FUCHSIA;
      }
      else
      {
        color = LIME;
      }

      LED(particles[f][2],particles[f][0],particles[f][1],color[0],color[1],color[2]);
      lastpart[f][2]=particles[f][2];
      lastpart[f][0]=particles[f][0];
      lastpart[f][1]=particles[f][1];
    }

    delay(20);
    for (f=0; f < numParticles; f++) {
      LED(lastpart[f][2], lastpart[f][0], lastpart[f][1], 0, 0, 0);
    }
  }
}

void knockYourselfOut()
{
  intro();
  Explode(20,10);
}
