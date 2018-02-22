public class c_char
{
    char cChar = ' ';
    byte[] charByte = new byte[1];

    public int getSize()
    {
        return 0;
    }

    public char getValue()
    {
        return cChar;
    }

    public void setValue(byte[] buf)
    {
        //TO-DO
    }

    public void setValue(char c)
    {
        //TO-DO
    }

    public byte toByte()
    {
        return charByte[0];
    }
}
