FROM ubuntu:16.04

# Update linux and install python
RUN apt-get update -y && \
    apt-get install -y python-pip python-dev

# We copy just the requirements.txt first to leverage Docker cache
COPY ./requirements.txt /app/requirements.txt

# Set working directory
WORKDIR /app

# Install requriements for python app
RUN pip install -r requirements.txt

# Set the entry point to python cli
ENTRYPOINT [ "python" ]

# Expose the Flask port
EXPOSE 5000

# Add VOLUME to allow real time actualization
VOLUME  ["/app"]

# Set the default command to run when starting the container
CMD [ "app.py" ]