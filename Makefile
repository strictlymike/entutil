TARGET = entutil

$(TARGET): bit_counts.c entropy_measurement.c entropy_util.c -lm
	$(CC) -o $@ $^

clean:
	$(RM) -f $(TARGET)
