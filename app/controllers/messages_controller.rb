class MessagesController < ApplicationController

	def index          
		@messages = Message.all
		render json: @messages
	end
	
	def latest
			@messages = Message.last
			render text: @messages.message	
	end

	def create
	  #create new message
	  @message = Message.new(:message => params[:message])
	  @message.save!
	  render nothing: true, status: 201
		#  if you want to debug. render text: params[:message].inspect
	end

end
