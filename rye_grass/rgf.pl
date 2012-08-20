#!/usr/bin/perl -w
# Reading Rice gff files
# Check column 3 for the term "gene", then take start (col 4) and stp location (col 5) and find if query
# location falls in that region. Col 7 is strand, Col 9 in name and description

print "Hello\n";

open(SOURCE, "linkage_edited.res") || die;
open(RICE_GFF, "rice_gffs/chr1.gff3") || die;

$line=<SOURCE>; # lose first line
@rads=<SOURCE>;

$line=<RICE_GFF>;   # lose first line
@data=<RICE_GFF>;

foreach my $rads (@rads)
{
	@rad = split(/, /, $rads);
	
	$_ = $rad[0];
	if(m/Chr1/)
	{
		$rad_loc = $rad[2];
		chomp $rads;
		print $rads;
		print ", ";
		
		foreach my $data (@data)
		{ 
			@tokens = split(/\t/, $data);
			#print $tokens[2];
			$_=$tokens[2];
			if(m/gene/)
			{
				#print "Found gene \n";
				if($tokens[3] < $rad_loc && $tokens[4] > $rad_loc)
				{
					@notes = split(/;/, $tokens[8]);
					print $notes[0];
					print ", ";
					print $notes[2];
					#print "\n";
				}
			}
		}
	}
}

close(RICE_GFF);


open(RICE_GFF, "rice_gffs/chr2.gff3") || die;
$line=<RICE_GFF>;   # lose first line
@data=<RICE_GFF>;

foreach my $rads (@rads)
{
	@rad = split(/, /, $rads);
	
	$_ = $rad[0];
	if(m/Chr2/)
	{
		$rad_loc = $rad[2];
		chomp $rads;
		print $rads;
		print ", ";
		
		foreach my $data (@data)
		{ 
			@tokens = split(/\t/, $data);
			#print $tokens[2];
			$_=$tokens[2];
			if(m/gene/)
			{
				#print "Found gene \n";
				if($tokens[3] < $rad_loc && $tokens[4] > $rad_loc)
				{
					@notes = split(/;/, $tokens[8]);
					print $notes[0];
					print ", ";
					print $notes[2];
					#print "\n";
				}
			}
		}
	}
}

close(RICE_GFF);


open(RICE_GFF, "rice_gffs/chr3.gff3") || die;
$line=<RICE_GFF>;   # lose first line
@data=<RICE_GFF>;

foreach my $rads (@rads)
{
	@rad = split(/, /, $rads);
	
	$_ = $rad[0];
	if(m/Chr3/)
	{
		$rad_loc = $rad[2];
		chomp $rads;
		print $rads;
		print ", ";
		
		foreach my $data (@data)
		{ 
			@tokens = split(/\t/, $data);
			#print $tokens[2];
			$_=$tokens[2];
			if(m/gene/)
			{
				#print "Found gene \n";
				if($tokens[3] < $rad_loc && $tokens[4] > $rad_loc)
				{
					@notes = split(/;/, $tokens[8]);
					print $notes[0];
					print ", ";
					print $notes[2];
					#print "\n";
				}
			}
		}
	}
}

close(RICE_GFF);

open(RICE_GFF, "rice_gffs/chr4.gff3") || die;
$line=<RICE_GFF>;   # lose first line
@data=<RICE_GFF>;

foreach my $rads (@rads)
{
	@rad = split(/, /, $rads);
	
	$_ = $rad[0];
	if(m/Chr4/)
	{
		$rad_loc = $rad[2];
		chomp $rads;
		print $rads;
		print ", ";
		
		foreach my $data (@data)
		{ 
			@tokens = split(/\t/, $data);
			#print $tokens[2];
			$_=$tokens[2];
			if(m/gene/)
			{
				#print "Found gene \n";
				if($tokens[3] < $rad_loc && $tokens[4] > $rad_loc)
				{
					@notes = split(/;/, $tokens[8]);
					print $notes[0];
					print ", ";
					print $notes[2];
					#print "\n";
				}
			}
		}
	}
}

close(RICE_GFF);

open(RICE_GFF, "rice_gffs/chr5.gff3") || die;
$line=<RICE_GFF>;   # lose first line
@data=<RICE_GFF>;

foreach my $rads (@rads)
{
	@rad = split(/, /, $rads);
	
	$_ = $rad[0];
	if(m/Chr5/)
	{
		$rad_loc = $rad[2];
		chomp $rads;
		print $rads;
		print ", ";
		
		foreach my $data (@data)
		{ 
			@tokens = split(/\t/, $data);
			#print $tokens[2];
			$_=$tokens[2];
			if(m/gene/)
			{
				#print "Found gene \n";
				if($tokens[3] < $rad_loc && $tokens[4] > $rad_loc)
				{
					@notes = split(/;/, $tokens[8]);
					print $notes[0];
					print ", ";
					print $notes[2];
					#print "\n";
				}
			}
		}
	}
}

close(RICE_GFF);

open(RICE_GFF, "rice_gffs/chr6.gff3") || die;
$line=<RICE_GFF>;   # lose first line
@data=<RICE_GFF>;

foreach my $rads (@rads)
{
	@rad = split(/, /, $rads);
	
	$_ = $rad[0];
	if(m/Chr6/)
	{
		$rad_loc = $rad[2];
		chomp $rads;
		print $rads;
		print ", ";
		
		foreach my $data (@data)
		{ 
			@tokens = split(/\t/, $data);
			#print $tokens[2];
			$_=$tokens[2];
			if(m/gene/)
			{
				#print "Found gene \n";
				if($tokens[3] < $rad_loc && $tokens[4] > $rad_loc)
				{
					@notes = split(/;/, $tokens[8]);
					print $notes[0];
					print ", ";
					print $notes[2];
					#print "\n";
				}
			}
		}
	}
}

close(RICE_GFF);

open(RICE_GFF, "rice_gffs/chr7.gff3") || die;
$line=<RICE_GFF>;   # lose first line
@data=<RICE_GFF>;

foreach my $rads (@rads)
{
	@rad = split(/, /, $rads);
	
	$_ = $rad[0];
	if(m/Chr7/)
	{
		$rad_loc = $rad[2];
		chomp $rads;
		print $rads;
		print ", ";
		
		foreach my $data (@data)
		{ 
			@tokens = split(/\t/, $data);
			#print $tokens[2];
			$_=$tokens[2];
			if(m/gene/)
			{
				#print "Found gene \n";
				if($tokens[3] < $rad_loc && $tokens[4] > $rad_loc)
				{
					@notes = split(/;/, $tokens[8]);
					print $notes[0];
					print ", ";
					print $notes[2];
					#print "\n";
				}
			}
		}
	}
}

close(RICE_GFF);

open(RICE_GFF, "rice_gffs/chr8.gff3") || die;
$line=<RICE_GFF>;   # lose first line
@data=<RICE_GFF>;

foreach my $rads (@rads)
{
	@rad = split(/, /, $rads);
	
	$_ = $rad[0];
	if(m/Chr8/)
	{
		$rad_loc = $rad[2];
		chomp $rads;
		print $rads;
		print ", ";
		
		foreach my $data (@data)
		{ 
			@tokens = split(/\t/, $data);
			#print $tokens[2];
			$_=$tokens[2];
			if(m/gene/)
			{
				#print "Found gene \n";
				if($tokens[3] < $rad_loc && $tokens[4] > $rad_loc)
				{
					@notes = split(/;/, $tokens[8]);
					print $notes[0];
					print ", ";
					print $notes[2];
					#print "\n";
				}
			}
		}
	}
}

close(RICE_GFF);

open(RICE_GFF, "rice_gffs/chr9.gff3") || die;
$line=<RICE_GFF>;   # lose first line
@data=<RICE_GFF>;

foreach my $rads (@rads)
{
	@rad = split(/, /, $rads);
	
	$_ = $rad[0];
	if(m/Chr9/)
	{
		$rad_loc = $rad[2];
		chomp $rads;
		print $rads;
		print ", ";
		
		foreach my $data (@data)
		{ 
			@tokens = split(/\t/, $data);
			#print $tokens[2];
			$_=$tokens[2];
			if(m/gene/)
			{
				#print "Found gene \n";
				if($tokens[3] < $rad_loc && $tokens[4] > $rad_loc)
				{
					@notes = split(/;/, $tokens[8]);
					print $notes[0];
					print ", ";
					print $notes[2];
					#print "\n";
				}
			}
		}
	}
}

close(RICE_GFF);

open(RICE_GFF, "rice_gffs/chr10.gff3") || die;
$line=<RICE_GFF>;   # lose first line
@data=<RICE_GFF>;

foreach my $rads (@rads)
{
	@rad = split(/, /, $rads);
	
	$_ = $rad[0];
	if(m/Chr10/)
	{
		$rad_loc = $rad[2];
		chomp $rads;
		print $rads;
		print ", ";
		
		foreach my $data (@data)
		{ 
			@tokens = split(/\t/, $data);
			#print $tokens[2];
			$_=$tokens[2];
			if(m/gene/)
			{
				#print "Found gene \n";
				if($tokens[3] < $rad_loc && $tokens[4] > $rad_loc)
				{
					@notes = split(/;/, $tokens[8]);
					print $notes[0];
					print ", ";
					print $notes[2];
					#print "\n";
				}
			}
		}
	}
}

close(RICE_GFF);

open(RICE_GFF, "rice_gffs/chr11.gff3") || die;
$line=<RICE_GFF>;   # lose first line
@data=<RICE_GFF>;

foreach my $rads (@rads)
{
	@rad = split(/, /, $rads);
	
	$_ = $rad[0];
	if(m/Chr11/)
	{
		$rad_loc = $rad[2];
		chomp $rads;
		print $rads;
		print ", ";
		
		foreach my $data (@data)
		{ 
			@tokens = split(/\t/, $data);
			#print $tokens[2];
			$_=$tokens[2];
			if(m/gene/)
			{
				#print "Found gene \n";
				if($tokens[3] < $rad_loc && $tokens[4] > $rad_loc)
				{
					@notes = split(/;/, $tokens[8]);
					print $notes[0];
					print ", ";
					print $notes[2];
					#print "\n";
				}
			}
		}
	}
}

close(RICE_GFF);

open(RICE_GFF, "rice_gffs/chr12.gff3") || die;
$line=<RICE_GFF>;   # lose first line
@data=<RICE_GFF>;

foreach my $rads (@rads)
{
	@rad = split(/, /, $rads);
	
	$_ = $rad[0];
	if(m/Chr12/)
	{
		$rad_loc = $rad[2];
		chomp $rads;
		print $rads;
		print ", ";
		
		foreach my $data (@data)
		{ 
			@tokens = split(/\t/, $data);
			#print $tokens[2];
			$_=$tokens[2];
			if(m/gene/)
			{
				#print "Found gene \n";
				if($tokens[3] < $rad_loc && $tokens[4] > $rad_loc)
				{
					@notes = split(/;/, $tokens[8]);
					print $notes[0];
					print ", ";
					print $notes[2];
					#print "\n";
				}
			}
		}
	}
}

close(RICE_GFF);