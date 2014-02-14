#!/usr/bin/perl -w
#
#  hw2.pl fastafile
#
#   @created on 8/31/08 by rdb
#   
#   @modified on 2/7/13 by Jeremy Dobbins-Bucklad for MCBS 913
#   

use warnings;
use strict;

my $usageMsg = q(   Usage: fastaparse fastafile
          Extract each sequence from a fastafile into a single string.
          Searches Open Reading Frames within each sequence for longest matches.
          
          Output is the sequence ID, frame #, length, and start position.
          Output sent to standard output.);


#+++++++++++++++++++++++ set file name here +++++++++++++++++++++++++++++
&checkUsage();
my $seqFile = $ARGV[ 0 ];   # comment this line if assigning file name above
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

open ( IN, $seqFile )  or die "Unable to open: ".$seqFile ;




#--------Read in all the fasta files--------#
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
while ( $header )	#While we're reading in headers
{
   $headers[$index] = $header;	#Save header
   my $seq = ""; 	#intialize string
   my $inLine = <IN>;	#grab first line

   # read in all input lines of bases
	#while we're reading lines & it's not a header
   while ( $inLine && substr( $inLine, 0, 1 ) ne '>' )	
   {
      chomp( $inLine );     # remove line feed with chomp!
      $seq = $seq . $inLine;	#String concat? Yep. String concat.
      $inLine = <IN>;	#Read a new line
   }
	$sequences[$index++] = $seq;	#save sequence
   $header = $inLine;    # last line read is either next header or null
}
#-----done reading-----#




#print "Sequences\n----------\n";
#foreach my $s(@sequences){ print "$s \n"; }
#print "Headers\n----------\n";
#foreach my $h(@headers){ print "$h \n"; }

#-----Look for largest open reading frame in each-----#
#create the search pattern for DNA
my $start = "ATG";
my $stop = "TAG|TAA|TGA";
my $codon = "[ATCG]{3}";
#Matches beginning of line, codons, and first stop codon
my $pattern = "^(($codon)+?($stop))";
my @orfs = {}; #saves largest orf per sequence at same index

#print "\npattern is '$pattern'\n\n";

#Process one sequence at a time
my $currSeq;
for ( my $i = 0; $i < @sequences; $i++ ){
	$currSeq = $sequences[$i];
	my @orfs = {"","","","","",""};	
	my $workingSeq;
	#print "currSeq = $currSeq\n";
	######forward match######
	for( my $j = 0; $j < 3; $j++ ){
		#get substring of sequence from j
		$workingSeq = substr($currSeq,$j);
		###find largest match
		my $match = $workingSeq =~ m|$pattern|g;
		#while( $match ){
		#	if( length($&) > length($orfs[$i]) ){
		#		print "\t$& > " .  "$orfs[$i]\n";
		#		$orfs[$i] = $&;	
		#	}
		#	$match = $workingSeq =~ m|$pattern|g;
		#}
		if( !defined($&) ){
			$orfs[$j] = "";
		}else{		
			$orfs[$j] = $&;
		}
	}
	
	######reverse complement######
	#1) Reverse string
	my $revSeq = reverse $currSeq;
	#print "1) $revSeq\n";

	#2) Replace nucs with complements
	$revSeq =~ tr/ACTG/TGAC/;
	#print "2) $revSeq\n\n";

	for( my $j = 0; $j < 3; $j++ ){
		#get substring of sequence from j
		$workingSeq = substr($revSeq,$j);
		#match
		$workingSeq =~ m|$pattern|;
		#Save matches from index 3-5
		if( !defined($&) ){
			$orfs[$j+3] = "";
		}else{		
			$orfs[$j+3] = $&;
		}
	}	
	
	######print out results######
	#pull out sequence ID
	my $hdr = $headers[$i];
	chomp $hdr;
	$hdr =~ m/>(.*?)\s/;
	#print "$1\n";
	###ERROR: Was getting weird 'unitialized value' messages after 
	# with the regex for seqID, so I just use the whole header
	my $seqID = substr($hdr,1);
	for ( my $k = 0; $k < @orfs; $k++ ){
		#seqID
		print "$seqID ";
		#frame number
		if( $k < 3 ){
			print "$k ";
		}else{
			my $var = "r" . ($k-1); 
			print "$var ";
		}
		#length
		my $length = length($orfs[$k]);
		#test for if a match came through		
		if( $length > 3 ){
			$length -= 3;
		}			
		print "$length ";
		#startPosition
		print ($k % 3);		
		print "\n";
	}

	print "\n";
	
}

#++++++++++++++++++ subroutine checkUsage() ++++++++++++++++++++++++++++++++
sub checkUsage()
{
   if ( @ARGV == 0 || $ARGV[0] eq "-h" )
   {
      print STDERR "$usageMsg\n";
      exit;
   }
}

