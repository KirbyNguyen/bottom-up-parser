package syntaticalanalysis;

import java.nio.file.Files;
import java.util.Stack;



public class main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		
		String input ="a+b$";
		char[] inputArray = input.toCharArray();
		
	
		Stack<String> myStack = new Stack();
	
		
		myStack.push("$");
		myStack.push("E");
		
	
		int index=0;
	
		while(myStack.size() > 1) {
				
				if(myStack.peek().equals(Character.toString(inputArray[index]))) {
					System.out.println(myStack);
					System.out.println("Matched Symbol: " + myStack.peek());
					if(!(Character.toString(inputArray[index+1]).equals(null)))
					index++;
					
					myStack.pop();
				}
				else if(Character.toString(inputArray[index]).matches("[(]") && myStack.peek().equals("E") ){
					System.out.println(myStack);
					System.out.println(inputArray[index]);
					System.out.println("RULE: 1");
					myStack.pop();
					myStack.push("Q");
					myStack.push("T");
				}				
				else if(myStack.peek().equals("E") && Character.toString(inputArray[index]).matches("[a-z]")){
					System.out.println(myStack);
					System.out.println(inputArray[index]);
					System.out.println("RULE: 1" );
					myStack.pop();
					myStack.push("Q");
					myStack.push("T");
				}	
				else if(myStack.peek().equals("Q") && Character.toString(inputArray[index]).matches("\\+")){
					System.out.println("RULE: 2" );
					myStack.pop();
					myStack.push("Q");
					myStack.push("T");
					myStack.push("+");
				}	
				else if(myStack.peek().equals("Q") && Character.toString(inputArray[index]).matches("\\-")){
					System.out.println("RULE: 3" );
					myStack.pop();
					myStack.push("Q");
					myStack.push("T");
					myStack.push("-");
				}	
				else if(myStack.peek().equals("Q") && Character.toString(inputArray[index]).matches("\\$")){
					System.out.println("RULE: 4" );
					myStack.pop();
				}	
				else if(myStack.peek().equals("Q") && Character.toString(inputArray[index]).matches("[)]")){
					System.out.println("RULE: 4" );
					myStack.pop();
					
				}	
				else if(myStack.peek().equals("T") && Character.toString(inputArray[index]).matches("[(]")){
					System.out.println(myStack);
					System.out.println(inputArray[index]);
					System.out.println("RULE: 5" );
					myStack.pop();
					myStack.push("R");
					myStack.push("F");
				}	
				else if(myStack.peek().equals("T") && Character.toString(inputArray[index]).matches("[a-z]")){
					System.out.println(myStack);
					System.out.println(inputArray[index]);
					System.out.println("RULE: 5" );
					myStack.pop();
					myStack.push("R");
					myStack.push("F");
				}	
				else if(myStack.peek().equals("R") && Character.toString(inputArray[index]).matches("\\+")){
					System.out.println("RULE: 8" );
					myStack.pop();
				}	
				else if(myStack.peek().equals("R") && Character.toString(inputArray[index]).matches("\\-")){
					System.out.println("RULE: 8" );
					myStack.pop();
				}	
				else if(myStack.peek().equals("R") && Character.toString(inputArray[index]).matches("\\*")){
					System.out.println("RULE: 6" );
					myStack.pop();
					myStack.push("R");
					myStack.push("F");
					myStack.push("*");
				}	
				else if(myStack.peek().equals("R") && Character.toString(inputArray[index]).matches("\\/")){
					System.out.println("RULE: 7" );
					myStack.pop();
					myStack.push("R");
					myStack.push("F");
					myStack.push("/");
				}	
				else if(myStack.peek().equals("R") && Character.toString(inputArray[index]).matches("[)]")){
					System.out.println("RULE: 8" );
					myStack.pop();
				}	
				else if(myStack.peek().equals("R") && Character.toString(inputArray[index]).matches("\\$")){
					System.out.println("RULE: 8" );
					myStack.pop();
				}	
				else if(myStack.peek().equals("F") && Character.toString(inputArray[index]).matches("[(]")){
					System.out.println("RULE: 9" );
					myStack.pop();
					myStack.push(")");
					myStack.push("E");
					myStack.push("(");
				}	
				else if(myStack.peek().equals("F") && Character.toString(inputArray[index]).matches("[a-z]")){
					System.out.println(myStack);
					System.out.println(inputArray[index]);
					System.out.println("RULE: 10" );
					myStack.pop();
					myStack.push("I");
				}	
				else if(myStack.peek().equals("I") && Character.toString(inputArray[index]).matches("[a-z]")){
					System.out.println(myStack);
					System.out.println(inputArray[index]);
					System.out.println("RULE: 11" );
					myStack.pop();
					myStack.push(Character.toString(inputArray[index]));
					System.out.println(myStack);
					System.out.println(inputArray[index]);
	
				}
				
		}
		System.out.println(myStack);
	}
		
}
