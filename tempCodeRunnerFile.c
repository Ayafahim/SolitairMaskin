  printf("Shuffeling...\n");
    int numShuffles = rand() % 91 + 10;
    for (int i = 0; i < numShuffles; i++)
    {
        shuffleList(&head);
    }