void printTime(int v) {
    int ones;
    int tens; 
    
    ones=v%10;
    v=v/10;
    tens=v%10;    
    
    lc.setDigit(0,0,(byte)tens,false);
    lc.setDigit(0,1,(byte)ones,false);
}

void printScore(int v) {
    int ones;
    int tens; 
    
    ones=v%10;
    v=v/10;
    tens=v%10;    
    
    lc.setDigit(0,2,(byte)tens,false);
    lc.setDigit(0,3,(byte)ones,false);
}

void printMaxScore(int v) {
    int ones;
    int tens; 
    
    ones=v%10;
    v=v/10;
    tens=v%10;    
    
    lc.setDigit(0,4,(byte)tens,false);
    lc.setDigit(0,5,(byte)ones,false);
}
