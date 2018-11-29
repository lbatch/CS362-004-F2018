

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	  assertEquals(true, validator.isValid("https://www.google.com"));
	  assertEquals(true, validator.isValid("ftp://www.google.com"));
	  assertEquals(true, validator.isValid("http://web.engr.oregonstate.edu/~onid"));
	  assertEquals(false, validator.isValid("3ht://web.engr.oregonstate.edu/~onid"));
	  assertEquals(false, validator.isValid("http://1.2.3.4.5/~onid"));
	  assertEquals(false, validator.isValid("http://web.engr.oregonstate.edu/../"));
   }
   
   
   public void testYourFirstPartition()
   {
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	 //No scheme
	 assertEquals(false, validator.isValid("www.google.com/"));

   }
   
   public void testYourSecondPartition(){
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	 // Valid scheme
	   assertEquals(true, validator.isValid("http://www.google.com/"));

   }

   public void testYourThirdPartition(){
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   // Invalid scheme
	   assertEquals(false, validator.isValid("3ht://www.google.com/"));
   }
   
   public void testYourFourthPartition(){
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   // No authority
	   assertEquals(false, validator.isValid("http:///"));
   }
 
   public void testYourFifthPartition(){
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   // Valid authority
	   assertEquals(true, validator.isValid("http://www.google.com/"));
   }

   public void testYourSixthPartition(){
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   // Invalid authority
	   assertEquals(false, validator.isValid("http://256.256.256.256/"));
   }
   
   public void testYourSeventhPartition(){
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   // No port
	   assertEquals(true, validator.isValid("http://www.google.com/"));

   }
   
   public void testYourEighthPartition(){
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   // Valid port
	   assertEquals(true, validator.isValid("http://www.google.com:80/"));
   }
   
   public void testYourNinthPartition(){
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   // Invalid port
	   assertEquals(false, validator.isValid("http://www.google.com:-1/"));
   }
   
   public void testYourTenthPartition(){
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   // No path
	   assertEquals(true, validator.isValid("http://www.google.com"));
   }

   public void testYourEleventhPartition(){
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   // Valid path
	   assertEquals(true, validator.isValid("http://www.google.com/test1"));
   }

   public void testYourTwelfthPartition(){
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   // Invalid path
	   assertEquals(false, validator.isValid("http://www.google.com/.."));
	   
   }
   
   public void testIsValid()
   {
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   String validSchemes[] = new String[3];
	   String invalidSchemes[] = new String[3];
	   
	   validSchemes[0] = "http://";
	   validSchemes[1] = "file://";
	   validSchemes[2] = "ftp://";

	   invalidSchemes[0] = "";
	   invalidSchemes[1] = "3ht://";
	   invalidSchemes[2] = "http:";
	   
	   String validAuthorities[] = new String[3];
	   String invalidAuthorities[] = new String[3];

	   validAuthorities[0] = "www.google.com";
	   validAuthorities[1] = "go.com";
	   validAuthorities[2] = "0.0.0.0";
	   
	   invalidAuthorities[0] = "";
	   invalidAuthorities[1] = "go.a";
	   invalidAuthorities[2] = "256.256.256.256";
	   
	   String validPorts[] = new String[3];
	   String invalidPorts[] = new String[3];
	   
	   validPorts[0] = "";
	   validPorts[1] = ":80";
	   validPorts[2] = ":65535";
	   
	   invalidPorts[0] = ":-1";
	   invalidPorts[1] = ":abc";
	   invalidPorts[2] = ":70000";
	   
	   String validPaths[] = new String[3];
	   String invalidPaths[] = new String[3];
	   
	   validPaths[0] = "";
	   validPaths[1] = "/test1";
	   validPaths[2] = "/test1/";
	   
	   invalidPaths[0] = "/..";
	   invalidPaths[1] = "/../";
	   invalidPaths[2] = "/#/file";
			 	   
	   for(int i = 0; i < 3; i++)
	   {
		   String url = "";
		   for(int j = 0; j < 3; j++)
		   {
			   for(int k = 0; k < 3; k++)
			   {
				   for(int l = 0; l < 3; l++)
				   {
					   url = validSchemes[i] + validAuthorities[j] + validPorts[k] + validPaths[l];
					   if(!validator.isValid(url))
					   {
						   System.out.println("Test failed: URL should have been true, evaluated to false:" + url);
					   }
				   }
			   }
		   }
	   }
	   
	   for(int i = 0; i < 3; i++)
	   {
		   String url = "";
		   for(int j = 0; j < 3; j++)
		   {
			   for(int k = 0; k < 3; k++)
			   {
				   for(int l = 0; l < 3; l++)
				   {
					   url = invalidSchemes[i] + validAuthorities[j] + validPorts[k] + validPaths[l];
					   if(!validator.isValid(url))
					   {
						   System.out.println("Test failed: URL should have been false, evaluated to true:" + url);
					   }
				   }
			   }
		   }
	   }
	   for(int i = 0; i < 3; i++)
	   {
		   String url = "";
		   for(int j = 0; j < 3; j++)
		   {
			   for(int k = 0; k < 3; k++)
			   {
				   for(int l = 0; l < 3; l++)
				   {
					   url = validSchemes[i] + invalidAuthorities[j] + validPorts[k] + validPaths[l];
					   if(validator.isValid(url))
					   {
						   System.out.println("Test failed: URL should have been false, evaluated to true:" + url);
					   }
				   }
			   }
		   }
	   }
	   for(int i = 0; i < 3; i++)
	   {
		   String url = "";
		   for(int j = 0; j < 3; j++)
		   {
			   for(int k = 0; k < 3; k++)
			   {
				   for(int l = 0; l < 3; l++)
				   {
					   url = validSchemes[i] + validAuthorities[j] + invalidPorts[k] + validPaths[l];
					   if(validator.isValid(url))
					   {
						   System.out.println("Test failed: URL should have been false, evaluated to true:" + url);
					   }
				   }
			   }
		   }
	   }
	   
	   for(int i = 0; i < 3; i++)
	   {
		   String url = "";
		   for(int j = 0; j < 3; j++)
		   {
			   for(int k = 0; k < 3; k++)
			   {
				   for(int l = 0; l < 3; l++)
				   {
					   url = validSchemes[i] + validAuthorities[j] + validPorts[k] + invalidPaths[l];
					   if(validator.isValid(url))
					   {
						   System.out.println("Test failed: URL should have been false, evaluated to true:" + url);
					   }
				   }
			   }
		   }
	   }

	   
   }

}
