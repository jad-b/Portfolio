#!/usr/bin/perl -w
#
#  fastaparse.pl fastafile
#
#   @created on 8/31/08 by rdb
#   
#   @modified on 1/31/13 by Jeremy Dobbins-Bucklad for MCBS 913
#   

use warnings;
use strict;
my $usageMsg = q(   Usage: fastaparse fastafile
          Extract each sequence from a fastafile into a single string.
          <do something to the sequence -- this one computes its length
          and adds it after the sequence name on the header>
          
          Output is the revised header and sequence data
          Output sent to standard output.);


#+++++++++++++++++++++++ set file name here +++++++++++++++++++++++++++++
# ----------------hard code the file name here:---------------------------
#my $seqFile = "dimer.fasta";  

#------------- OR --------------- uncomment next 2 lines to read cmd line

&checkUsage();
my $seqFile = $ARGV[ 0 ];   # comment this line if assigning file name above
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

open ( IN, $seqFile )  or die "Unable to open: ".$seqFile ;

# first line better be a sequence header
my $header = <IN>;	#Read from stdin
if ( substr( $header, 0, 1 ) ne '>' )#if there's not a '>', print error	
{
   print "********* ERROR ********* Expecting header, got:\n $header";
   print " is this a fasta file??? ";
   exit;
}
my @headers,my @sequences;
my $index = 0;
while ( $header )	#While we're reading in anything
{
   $headers[$index] = $header;	#Save header
   my $seq = ""; 	#intialize string
   my $inLine = <IN>;	#grab first line

   # read in all input lines of bases
   while ( $inLine && substr( $inLine, 0, 1 ) ne '>' )	#while we're reading lines & it's not a header
   {
      chomp( $inLine );     # remove line feed with chomp!
      #print "inline: $inLine\n";
      $seq = $seq . $inLine;	#String concat? Yep. String concat.
      #print "After: $seq\n";
      $inLine = <IN>;	#Read a new line
   }
	#print "----Final seq----\n$seq\n";
	#print "$header$seq\n";
	$sequences[$index++] = $seq;	#save sequence
   # -----------------------------------------------------
   #  Replace the lines below with the sequence specific
   #  processing you want to do.
   #
   #my $basesCount = length( $seq );				#All my bases belong to perl
   #&reviseHeaderAndPrint( $header, $basesCount, $seq );	#Method call? Yup. Method call.
	
   #--------------------------------------------------------
   $header = $inLine;    # last line read is either next header or null
}

#print "@headers";
my $numSeqs = @sequences;
#print "Sequences($numSeqs):\n@sequences\n";
##########################################
#jdb - my plan for motif searches.
#Save headers and sequences to arrays, then
#search the sequences for the pattern.
#Save the results to an array, and generate
#output.
##########################################
my $ptrn;
my $count; 
print "Please enter your search motif: ";
while( $ptrn = <STDIN> ){	
	chomp($ptrn);		
	print "Results:\n";		
	for( my $i = 0; $i < @sequences; $i++ ){
		#global match on sequence, save results to array
		my @results = $sequences[$i] =~ /$ptrn/g;
		#print "results($i): @results\n";	
		#Check number of matches found
		if( $count = @results ){	
			my $tempHdr = $headers[$i];
			chomp($tempHdr);
			print "$tempHdr $ptrn $count\n";	
		} 
	}	
	print "Please enter your search motif: ";
}


#&userInput();
	
# Grab user input in a loop
sub userInput(){
	print "Please enter your search pattern: ";
	my $line;
	while($line = <STDIN>){
		print "$line";
		print "Please enter your search pattern: ";
	}
}

#Search seq array for search pattern
#my @results;
#for each my $seqn(@sequences){#
#	$result = $seqn =~ /*/;
#}

#++++++++++++++++++ subroutine checkUsage() ++++++++++++++++++++++++++++++++
sub checkUsage()
{
   if ( @ARGV == 0 || $ARGV[0] eq "-h" )
   {
      print STDERR "$usageMsg\n";
      exit;
   }
}
#++++++++++++++++++ subroutine reviseHeaderAndPrint ++++++++++++++++++++++++
#
# This subroutine inserts the base count into the header and prints the
# new header and sequence
#
sub reviseHeaderAndPrint()
{
   my ( $hdr, $count, $seq ) = @_;    # some magic to get the parameters
   #
   #------------------------------------------------------
   #------ split the header line into an array containing
   #  one "word" per entry. A "word" or token is any sequence of
   #  non-blank characters separated by 1 or more blanks.
   #           
   #  first token is the sequence name (along with the '>')
   
   chop( $hdr );
   $hdr = $hdr . " " ;    # make sure there IS a blank in the header
   my $blank = index( $hdr, " " );

   # insert the count right after the sequence name
   $hdr = substr( $hdr, 0, $blank ) 
                 . " $count " . substr( $hdr, $blank + 1 );
   &printSequence( $hdr, $seq );
   
}#++++++++++++++++++++++++++ subroutine printSequence ++++++++++++++++++++++++++
#
# This subroutine prints out a sequence with a possibly modified header
#  Parameters are the header and the sequence data
#
sub printSequence()
{
   my ( $hdr, $seqData ) = @_;    # some magic to get the parameters
   print "$hdr\n";
   
   # now print the sequence, 60 characters per line
   my @outLines = unpack( "(A60)*", $seqData );    # unpack to an array of lines
   foreach my $outLine( @outLines )
   {
      #print "$outLine\n";
   }      
}
